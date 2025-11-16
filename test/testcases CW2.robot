*** Settings ***
Documentation    Embedded Systems CW2 Project - Manual Test Cases

*** Test Cases ***

Test Button1 Increase High Limit
    [Documentation]    Press Button1 and check if High Limit increases by 10
    # Arrange
    Set initial High Limit to 1000
    # Act
    Press Button1 physically
    # Assert / Manual Result
    [Manual Check]    Did High Limit increase by 10? SUCCESS 

Test Button2 Decrease High Limit
    [Documentation]    Press Button2 and check if High Limit decreases by 10
    # Arrange
    Set initial High Limit to 1000
    # Act
    Press Button2 physically
    # Assert / Manual Result
    [Manual Check]    Did High Limit decrease by 10? SUCCESS 

Test LED ON Function
    [Documentation]    LED should turn on when sensor value is between LL and LH
    # Arrange
    Set LL = 500, LH = 1000, Sensor = 700
    # Act
    Observe LED physically
    # Assert / Manual Result
    [Manual Check]    Is LED ON? SUCCESS 

Test LED OFF Function
    [Documentation]    LED should turn off when sensor value is outside LL and LH
    # Arrange
    Set LL = 500, LH = 1000, Sensor = 1200
    # Act
    Observe LED physically
    # Assert / Manual Result
    [Manual Check]    Is LED OFF? SUCCESS

Test ADC Read
    [Documentation]    ADC should return a value between 0 and 1023
    # Act
    Read ADC channel 0
    # Assert / Manual Result
    [Manual Check]    Is ADC value between 0–1023? SUCCESS 

Test LCD Display
    [Documentation]    LCD should show LL, LH, Sensor, and LED status correctly
    # Arrange
    LL = 500, LH = 1000, Sensor = 700
    # Act
    Call LCD_Display(LL, LH, Sensor)
    # Assert / Manual Result
    [Manual Check]    Does LCD show correct values and LED status? SUCCESS 
