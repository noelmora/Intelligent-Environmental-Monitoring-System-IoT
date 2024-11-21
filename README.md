# Intelligent Environmental Monitoring System with AI-Based Recommendations

## Project Description
This project is designed to monitor and analyze environmental and climate variables in real time, such as temperature, humidity, air quality, light, and noise levels. Our system is able to collect this information through various sensors connected to a microcontroller, and then display the data on a web page in an accessible and visually clear way.

What makes this project unique is the integration of artificial intelligence, which allows data to be analyzed and practical recommendations to be generated both to optimize the physical environment and the well-being of people in that space. With this feature, we are not only capturing data, but we are using it to offer useful insights and personalized advice that improve the quality of life in indoor environments.

## Objectives
* Real-Time Environmental Monitoring: Provide a system capable of capturing, processing and presenting environmental data in real time.
* AI-Based Recommendations: Generate practical suggestions to improve the physical environment and people's comfort, leveraging the capabilities of an AI API.
* User-Friendly Interface: Display the collected information in a clear and easy-to-use web interface.

## Project Components
For the development of this project we have used a carefully selected combination of hardware and software. Each component plays a crucial role in the collection and presentation of environmental data.

### 1. Hardware
* ESP32 Microcontroller: The ESP32 is the brain of the system. With its built-in Wi-Fi connectivity and processing power, it can collect data from sensors and transmit it to the website. The ESP32 was chosen for its energy efficiency and robustness in handling multiple sensors.
* DHT22 Temperature and Humidity Sensor: This sensor can measure both the temperature and relative humidity of the environment. With a measurement range suitable for most indoor environments, the DHT22 offers high accuracy, ensuring reliable data for analysis.
* MQ-135 Air Quality Sensor: This sensor measures air quality levels, detecting concentrations of polluting gases. This is essential for closed environments, where ventilation may be limited.
* Light Sensor (LDR): The LDR light sensor measures the light intensity of the environment. This allows us to know if the environment has adequate lighting, which is important for both comfort and productivity.
* KY-037 Noise Sensor: This sensor measures noise levels in the environment. It is useful for detecting whether the environment is prone to noise pollution, which can affect people's concentration and comfort.
* Other Auxiliary Components: In addition, we have used resistors, cables, and breadboards to assemble the circuit and connect each component safely and efficiently.

### 2. Technologies Used
For the development of the web interface and the programming of the microcontroller, we have used the following technologies:
* HTML, CSS, JavaScript: These languages ​​form the basis of our website. HTML and CSS are used to structure and design the interface, while JavaScript manages the communication with the microcontroller and the dynamic display of data in real time.
* Arduino IDE: It was used to program the ESP32 microcontroller, loading the code that allows the reading of sensors and the sending of data to the web server.
* C (Arduino-oriented): The ESP32 code is written in C, adapted for the Arduino environment, allowing for precise and efficient control of the sensors.

### 3. Artificial Intelligence Integration
AI is the innovative component of this project. Through an AI API, we send the data from the environment (temperature, humidity, air quality, etc.) and get recommendations tailored to both the environment and the people present. This API allows the data to be interpreted and natural language recommendations to be generated that are displayed on the website.

For example:

If the air quality is low, AI can suggest improving ventilation.
If the temperature is high and the humidity is high, it can recommend the use of dehumidifiers or hydration for people.
This functionality allows the system to not only inform, but also act as a virtual assistant to optimize the environment.

## System Operation
1. Data Capture: The ESP32 microcontroller takes readings from the sensors at predefined intervals and sends the data to the web server.
2. Communication with AI API: Each time a new set of data is received, the server sends this information to the AI ​​API, requesting recommendations based on the current values.
3. Display on the Web Page: The sensor information and AI recommendations are displayed in real time on the web page, where the user can consult both the current data and the generated suggestions.
4. Continuous Update: The system works continuously, updating data and recommendations as environmental conditions change.

## Example of use
A typical example of use could be in an office or closed room where CO2 levels tend to rise. The system can detect this condition and recommend opening a window to ventilate the environment, helping to prevent fatigue and improve concentration. In another case, it could alert about high humidity and suggest the use of dehumidifiers.

## Operation
We embed code in the ESP32 development board to analyze environmental variables using sensors and for the use of AI we use the Gemini API, but for this we create another AI that we store in Vercel to be able to consult this AI to the other AI

![image](https://github.com/user-attachments/assets/9a6771b0-f85a-4e34-aa5e-95e29b59af87)

![image](https://github.com/user-attachments/assets/cc6f2b33-f7f5-43a6-93e1-96264503e76d)

![image](https://github.com/user-attachments/assets/02391387-eee2-4440-8578-2c619dd8cc5f)

![image](https://github.com/user-attachments/assets/6bdae549-b618-46a1-a785-ad49775dab32)

![image](https://github.com/user-attachments/assets/e8c2c231-e567-4e22-8c6d-4c37f8570c91)

![image](https://github.com/user-attachments/assets/7fd81beb-4f72-447f-bdd2-03570350af16)

![image](https://github.com/user-attachments/assets/f153d0a3-7520-441a-9dcb-d32c605c399c)

## Authors
* Manuel Rodriguez
* Noel Mora
* Sergio Claustro
