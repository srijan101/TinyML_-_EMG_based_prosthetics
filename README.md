TinyML-Based Prosthetic Hand 🤖✋
This project uses TinyML and EMG signals to control a prosthetic hand. The system collects muscle activity data via an EMG sensor, trains a machine learning model, and deploys it on a microcontroller to control servo motors, replicating hand gestures for amputees.

Features
✅ EMG Data Collection – Reads muscle signals, visualizes them, and saves them to an Excel file.
✅ TinyML Model Training – Converts EMG data into a model optimized for microcontrollers.
✅ Real-Time Servo Control – Runs the trained model and moves servos based on detected signals.
✅ ESP32 Communication – Data is exchanged via serial between the ESP and laptop.

Workflow
1️⃣ Data Collection – EMG signals are recorded and visualized.
2️⃣ Model Training – The collected data is used to train a TinyML model.
3️⃣ Deployment – The trained model is loaded onto the ESP32.
4️⃣ Gesture Control – The ESP32 runs the model and controls servos based on muscle activity.

Hardware Requirements
ESP32 / Microcontroller
EMG Sensor (e.g., MyoWare, Delsys)
Servo Motors
Laptop for Training
Setup & Usage
Connect the EMG sensor to the ESP32.
Run the data collection script to visualize and save muscle activity.
Train the TinyML model using the collected data.
Deploy the model to the ESP32 and run the servo control script.
🚀 This project aims to bring AI-powered prosthetics to life!
