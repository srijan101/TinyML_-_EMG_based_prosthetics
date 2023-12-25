//Tensorflow model converted to C++
#include "modeldata.h"
#include "functions.h"
#include "motor.h"
//Tensorflow custom library for ESP32
#include <TensorFlowLite_ESP32.h>
//experimental versions of regular Tensorflow headers
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize the LCD. The parameters may vary depending on your LCD model.
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;
int inference_count = 0;

constexpr int kTensorArenaSize = 30 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {
  Serial.begin(115200);
  setupServos();  // Setup the servo motors

    lcd.init();  // initialize the lcd 
  lcd.backlight();  // turn on the backlight
    // Set initial positions
  myservo1.write(0);  // Initial position for servo on pin 12
  myservo2.write(180);  // Initial position for servo on pin 13
  myservo3.write(180);  // Initial position for servo on pin 14
  myservo4.write(180);  // Initial position for servo on pin 25
  myservo5.write(180);  // Initial position for servo on pin 26

  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report(
        "Model provided is schema version %d not equal "
        "to supported version %d.",
        model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

static tflite::AllOpsResolver resolver;
  
static tflite::MicroInterpreter static_interpreter(
    model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    error_reporter->Report("AllocateTensors() failed");
    return;
  }

  input = interpreter->input(0);
  output = interpreter->output(0);

  inference_count = 0;
}

void loop() {
  float (*input_data)[2] = prelim_collection();  // Adjusted for two channels
  if (input_data == nullptr) {
    return;
  }
  
  // Print the array
  Serial.println("Printing input data array:");
  for (int i = 0; i < 100; i++) {  // Adjusted for 100 data points
    Serial.print(input_data[i][0]);
    Serial.print(", ");
    Serial.print(input_data[i][1]);
    Serial.print(", ");
    if ((i + 1) % 25 == 0) {
      Serial.println();
    }
  }
Serial.println();

  for (int i = 0; i < 100; i++) {  // Adjusted for 100 data points
    input->data.f[2*i] = float(input_data[i][0]);
    input->data.f[2*i+1] = float(input_data[i][1]);
  }

  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter->Report("Invoke failed on x_val");
    return;
  }

  // Find the gesture with the highest probability
  float max_prob = 0.0;
  int max_idx = -1;
  for (int i = 0; i < 5; i++) {
    if (output->data.f[i] > max_prob) {
      max_prob = output->data.f[i];
      max_idx = i;
    }
  }

  Serial.println("----------------------------------");
  Serial.print("MODEL OUTPUT: Open Hand:");
  Serial.print(output->data.f[0]);
  Serial.print(", Thumb Closed: ");
  Serial.print(output->data.f[1]);
  Serial.print(", Gripping Open: ");
  Serial.print(output->data.f[2]);
  Serial.print(", Four-Finger: ");
  Serial.print(output->data.f[3]);
  Serial.print(", Closed Fist: ");
  Serial.println(output->data.f[4]);

if (max_prob > 0.5) {
    String gesture;
    switch (max_idx) {
      case 0:
        gesture = "Open Hand";
        rotateServos(0, 180, 180, 180, 180);
        break;
      case 1:
        gesture = "Thumb Closed";
        rotateServos(0, 180, 180, 180, 90);
        break;
      case 2:
        gesture = "Gripping Open";
        rotateServos(90, 100, 100, 100, 100);
        break;
      case 3:
        gesture = "Four-Finger";
        rotateServos(110, 80, 80, 80, 180);
        break;
      case 4:
        gesture = "Closed Fist";
        rotateServos(110, 80, 80, 80, 80);
        break;
    }

    lcd.clear();  // clear the LCD
    lcd.setCursor(0, 0);  // set the cursor to the top-left corner
    lcd.print("Gesture:");  // print "Gesture:"
    lcd.setCursor(0, 1);  // move the cursor to the second line
    lcd.print(gesture);  // print the gesture
  }



  float y_val = output->data.f[0];
  inference_count += 1;
  if (inference_count >= 5000) inference_count = 0;
  delay(2000); // Delay increased to 2000 milliseconds


}// edited 
