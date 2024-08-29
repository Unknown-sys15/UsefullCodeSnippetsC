/////////////////////////HIH i2c/////////////////////

// Display the values on the LCD
//   Lcd_Out(1, 1, temp_str);  // Print the temperature on the first row
//   Lcd_Out(2, 1, hum_str);   // Print the humidity on the second row

// INITIALIZATION
void I2C_Init()
{
    I2C1_Init(100000); // Initialize I2C module at 200kHz
}

// VARIABLE DECLARATION
unsigned char sensorData[4]; // Buffer to hold sensor data
unsigned int humidity;
unsigned int temperature;
const float multiplier = 100.0 / 16383.0;
float humidity_value;
float temp_value;
// char temp_str[16] = "init"; // Buffer to hold temperature string
// char hum_str[16] = "init";  // Buffer to hold humidity string
float last_valid_temp = 0.0;
float last_valid_hum = 0.0;

// HIH READ FUNCTION
void HIH7000_Read()
{
    I2C1_Start();           // Issue I2C start signal
    I2C1_Wr(0x27 << 1 | 0); // Send HIH7000 address with R/W bit set to 0 (write)
    Delay_ms(50);
    I2C1_Repeated_Start();  // Issue a repeated start signal
    I2C1_Wr(0x27 << 1 | 1); // Send HIH7000 address with R/W bit set to 1 (read)

    sensorData[0] = I2C1_Rd(1); // Read first byte with ACK
    sensorData[1] = I2C1_Rd(1); // Read second byte with ACK
    sensorData[2] = I2C1_Rd(1); // Read third byte with ACK
    sensorData[3] = I2C1_Rd(0); // Read fourth byte with NACK (end of data)

    I2C1_Stop(); // Issue I2C stop signal

    if ((sensorData[0] & 0xC0) == 0x00)
    { // returns 00
        // Process the data
        humidity = ((sensorData[0] & 0x3F) << 8) | sensorData[1];    // Mask the two status bits and combine bytes
        temperature = ((sensorData[2] << 6) | (sensorData[3] >> 2)); // Combine the temperature bytes

        // Convert to human-readable values (Humidity in %RH and Temperature in �C)
        humidity_value = humidity * multiplier;
        temp_value = (temperature / 16383.0); // Convert to Celsius
        temp_value = temp_value * 165.0;
        temp_value = temp_value - 40.0;

        // Update last valid readings
        last_valid_temp = temp_value;
        last_valid_hum = humidity_value;

        // Format the floats into strings with sprintf
        sprintf(temp_str, "Temp: %.2fC    ", temp_value);      // Format temperature with 2 decimal places
        sprintf(hum_str, "Hum:  %.2f%%     ", humidity_value); // Format humidity with 2 decimal places
    }
    else if ((sensorData[0] & 0xC0) == 0x40)
    { // return 01
        // Use last valid readings
        sprintf(temp_str, "Temp: %.2fC", last_valid_temp);
        sprintf(hum_str, "Hum:  %.2f%%", last_valid_hum);
        // Optionally, retry reading the sensor after a delay
    }
    else if ((sensorData[0] & 0xC0) == 0x80)
    { // return 01
        sprintf(temp_str, "Temp: Comand mode");
        sprintf(hum_str, "Hum: Comand mode");
    }
    else
    {
        // If the data is not valid, show error message or retry
        sprintf(temp_str, "Temp: Error");
        sprintf(hum_str, "Hum: Error");
    }
}
///////////////////////////////////////////////////

// unsigned int TikHih = 0;
// unsigned int hihstate = 0;
unsigned int OldHih = 0;
void HihCall()
{
    // TikHih = TMR0L;
    if ((timerValue - OldHih) >= 3906 * 2)
    { // Ce je cas potekel  -> 500ms zdej
        OldHih = timerValue;
        HIH7000_Read();
    }
}