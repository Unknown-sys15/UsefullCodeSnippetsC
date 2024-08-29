void eprom_write(short address,short eeprom_loc,int podatki)
{
  I2C1_Start();                  // Start I2C communication
    I2C1_Wr(address);              // Send EEPROM device address + Write bit
    I2C1_Wr(eeprom_loc);           // Send EEPROM memory location
    I2C1_Wr((podatki >> 8) & 0xFF);  // Write high byte of 'podatki'
    I2C1_Wr(podatki & 0xFF);       // Write low byte of 'podatki'
    I2C1_Stop();                   // Stop I2C communication

    // EEPROM write delay (5ms to ensure data is written)
    delay_ms(5);
}

int eprom_read(short address,short eeprom_loc)
{
  int read_podatki;
    unsigned char high_byte, low_byte;

    I2C1_Start();                 // Start I2C communication
    I2C1_Wr(address);             // Send EEPROM address
    I2C1_Wr(eeprom_loc);          // Send EEPROM memory location
    I2C1_Repeated_Start();        // Issue a repeated start for reading
    I2C1_Wr(address | 0x01);      // Send EEPROM address with read bit
    high_byte = I2C1_Rd(1);       // Read high byte (ACK)
    low_byte = I2C1_Rd(0);        // Read low byte (No ACK)
    I2C1_Stop();                  // Stop I2C communication

    // Combine the high and low bytes to form the integer
    read_podatki = (high_byte << 8) | low_byte;
    return read_podatki;
}


//frequency =  eprom_read(0xA1,0x02);
//duty =  eprom_read(0xA1,0x04);


    /*
I2C1_Start();              // issue I2C start signal
           I2C1_Wr(0xA0);             // send byte via I2C  (device address + W)
           //I2C1_Wr(0x00);                //
           I2C1_Wr(0x02);                // send byte (address of EEPROM location)
           I2C1_Wr(frequency);             // send data (data to be written)
           I2C1_Stop();               // issue I2C stop signal

           delay_ms(1000);
           eprom_write(0xA0,0x04,duty);    */