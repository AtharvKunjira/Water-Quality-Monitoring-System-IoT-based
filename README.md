Water Quality Monitoring System (IoT-Based)

## 📌 Overview

The **Water Quality Monitoring System** is an IoT-based environmental monitoring solution designed for natural water bodies such as lakes, ponds, and reservoirs.

The system measures critical water quality parameters and displays the data both locally (via an OLED screen) and remotely through a web dashboard. To improve reliability, readings are processed using averaging techniques before being displayed and transmitted.

---

## ⚙️ Key Features

* 📟 Real-time data display on OLED screen
* 🌐 Interactive web dashboard
* 📊 Linear graph showing last 15 readings
* 📄 Downloadable text file containing last 15 readings
* 🍩 Doughnut chart indicating safety level (Safe / Moderate / Harmful)
* 📈 Averaged sensor readings for stability
* ⏱ Customizable sampling interval
* 🧪 Calibration implemented (testing phase)

---

## 🧪 Parameters Monitored

The system measures:

* **TDS (Total Dissolved Solids)**
* **Turbidity**
* **Water Temperature**

---

## 📈 Data Processing Method

To reduce sensor noise and increase stability:

* Each reading is taken over a **3-second interval**
* A total of **3 readings** are captured
* The **average of the 3 readings** is calculated
* The averaged value is displayed on OLED and updated on the dashboard
* Sampling interval is customizable in firmware

> Calibration is currently configured for testing purposes.

---

## 📊 Web Dashboard Features

The dashboard provides:

### 📉 1. Linear Graph

* Displays the **last 15 recorded readings**
* Helps visualize trends and fluctuations

### 📄 2. Downloadable Data File

* Allows users to download a **text file containing the last 15 readings**
* Useful for analysis and record keeping

### 🍩 3. Doughnut Chart (Safety Indicator)

* Displays current sensor status
* Categorizes readings as:

  * **Safe**
  * **Moderate**
  * **Harmful**
* Provides quick visual understanding of water condition

---

## 🖥️ Hardware Components

* Arduino-based microcontroller
* OLED Display
* TDS Sensor
* Turbidity Sensor
* Temperature Probe
* WiFi module for IoT connectivity

---

## 📂 Project Structure

```
/firmware        → Arduino source code
/dashboard       → Web interface files
README.md
LICENSE
.gitignore
```

---

## 🔐 Security

* WiFi credentials stored separately (`secrets.h`)
* Sensitive files excluded using `.gitignore`

---

## 📜 License

Licensed under the **GNU General Public License v3.0 (GPL-3.0)**.

---

## 🎓 Academic Purpose

Developed as an IoT-based environmental monitoring system for academic and research applications.

---

If you'd like, I can also:

* Add a **Future Improvements** section (AI prediction, cloud logging, mobile app)
* Add a **System Architecture diagram explanation**
* Make it more technical (for final year thesis)
* Make it shorter (for portfolio)

Tell me how you're presenting this project 👌
