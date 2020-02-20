# 13.02.2020
1) Blink LED on board, with Atmel and Arduino IDE.
2) Read the white paper/website of the board [https://learn.sodaq.com/Boards/Sara_AFF/#pin-definitions]
3) Contact Alberto for the microphone code (existing code of the MSc student)
4) Decide on the Atmel or Arduino IDE

# 20.02.2020
Metting with Alberto:
 - Phonometer app - use for calibrating
 - FPGA
   - connect to FPGA over SPI 
   - do addition on FPGA SPI 
   - migrate heavy computation code from phonometer (sw) to FPGA
   - sound classification algorithm - next semester
 - design with extending in mind: loudness sensor, pollution sensor
 - accelerometer - consider in the case of a car moving, you need to only measure for when it's stopped 
 - microphone is not very precise; maybe external board with analog parts
