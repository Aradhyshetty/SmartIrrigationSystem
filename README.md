# Smart Irrigation System Based on Crop Type 🌱💧

This project is a cost-effective, IoT-based smart irrigation system that automates water supply to crops based on real-time environmental conditions and specific crop water requirements. It is designed to help farmers reduce water usage, improve crop yield, and promote sustainable agriculture.

## 📌 Project Overview

With agriculture being a vital part of the economy, managing water efficiently is crucial. This system enables farmers to:
- Select crop type via a cloud interface.
- Monitor soil moisture and environmental conditions (humidity, temperature).
- Automate irrigation using predefined thresholds for each crop.
- Get real-time updates via cloud notifications.

## 🔧 Features

- 🌾 **Crop-Based Irrigation**: Automatically calculates water needs based on selected crop.
- 🌡️ **Real-time Sensor Monitoring**: Uses DHT22 and soil moisture sensors.
- 💻 **Cloud Integration**: Sends and receives data using Ubidots (via MQTT).
- 🔔 **Notification System**: Informs users when water is or isn't required.
- 🛠️ **Low-Cost Hardware**: Built with ESP8266, sensors, and relay module.
- ♻️ **Water Flow Control**: Prevents over-irrigation with servo motor-controlled flow.

## 🧰 Technologies Used

### 🔌 Hardware
- ESP8266 Wi-Fi Module
- DHT22 Temperature and Humidity Sensor
- Soil Moisture Sensor
- Water Level Sensor
- Water Pump
- Relay Module
- Servo Motor
- Jumper Wires, Breadboard

### 💻 Software
- Arduino IDE
- Ubidots IoT Cloud Platform
- MQTT Protocol
- DHT and Wi-Fi libraries

## 📊 System Architecture

The project follows a three-layer IoT architecture:
1. **Perception Layer** – Sensing: soil moisture, water level, temperature, humidity.
2. **Network Layer** – Transmitting data to/from cloud.
3. **Application Layer** – Decision making, visualization, and automation logic.

## 📷 Model Snapshots

[Model View 1](images/model_view1.jpg)(https://github.com/user-attachments/assets/263fd746-d7f8-418d-91f4-10da3e474c7b)
[Ubidots Dashboard](https://github.com/user-attachments/assets/7b887f0e-2bd2-49bc-9017-b994085609e0")


![Model View 2]("https://github.com/user-attachments/assets/f0405869-662e-451b-94a0-87a5cabb474d" )
![Model View 2](https://github.com/user-attachments/assets/3f83fcab-9d18-4462-bd64-48a2ff54fd28" )

*(You can upload the images in the repo and link them here)*

## 📈 Results

- ✔️ Efficient water management based on crop type
- ✔️ Reduced manual labor with full automation
- ✔️ Cloud monitoring and remote control
- ✔️ Optimized resource usage and crop yield

## ✅ Advantages

- Cost-effective and easy to implement
- Supports multiple crop types
- Scalable and adaptable across regions and seasons
- Ideal for small and marginal farmers

## 🚀 Future Scope

- Solar integration for energy efficiency
- Expand to mobile apps for better farmer accessibility
- AI for crop health prediction

## 📚 References

- Nandhini et al. (2017), Arduino-based smart irrigation using IoT.
- Pernapati (2018), IoT-based low-cost smart irrigation system.
- Singla et al. (2019), Wireless sensor networks for water conservation.
- Singh (2019), Scalable cloud-integrated IoT irrigation.
- Tak (2024), ESP32-based smart irrigation with Blynk.

---

## 📁 How to Use

1. Clone the repository:
```bash
git clone https://github.com/your-username/smart-irrigation.git
