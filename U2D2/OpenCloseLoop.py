
try:
    import time
    
    from dynamixel_sdk import * # Uses Dynamixel SDK library
    
    import os
    
    if os.name == 'nt':
        import msvcrt
        def getch():
            return msvcrt.getch().decode()
    else:
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        def getch():
            try:
                tty.setraw(sys.stdin.fileno())
                ch = sys.stdin.read(1)
            finally:
                termios.tcseattr(fd, termios.TCSADRAIN, old_settings)
            return ch
    
    
    
    
    ADDR_TORQUE_ENABLE          = 64
    ADDR_GOAL_POSITION          = 116
    ADDR_PRESENT_POSITION       = 132
    DXL_MINIMUM_POSITION_VALUE  = 1         # Refer to the Minimum Position Limit of product eManual
    DXL_MAXIMUM_POSITION_VALUE  = 4094      # Refer to the Maximum Position Limit of product eManual
    BAUDRATE                    = 1000000

    
    # DYNAMIXEL Protocol Version (1.0 / 2.0)
    # https://emanual.robotis.com/docs/en/dxl/protocol2/
    PROTOCOL_VERSION            = 2.0
    
    # Factory default ID of all DYNAMIXEL is 1
    DXL1_ID                     = 1
    DXL2_ID                     = 2
    DXL3_ID                     = 3
    DXL4_ID                     = 4
    DXL5_ID                     = 5
    # Use the actual port assigned to the U2D2.
    # ex) Windows: "COM*", Linux: "/dev/ttyUSB*", Mac: "/dev/tty.usbserial-*"
    DEVICENAME                  = 'COM7'
    
    TORQUE_ENABLE               = 1     # Value for enabling the torque
    TORQUE_DISABLE              = 0     # Value for disabling the torque
    DXL_MOVING_STATUS_THRESHOLD = 20    # Dynamixel moving status threshold
    
    index = 0
    
    dxl_goal_position1 = [1024, 3072]         # Goal position
    dxl_goal_position2 = [2000, 900]
    dxl_goal_position3 = [3000, 800]         # Goal position
    dxl_goal_position4 = [3100, 1050]
    dxl_goal_position5 = [2800, 1800]
    
    
    # Initialize PortHandler instance
    # Set the port path
    # Get methods and members of PortHandlerLinux or PortHandlerWindows
    portHandler = PortHandler(DEVICENAME)
    
    # Initialize PacketHandler instance
    # Set the protocol version
    # Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
    packetHandler = PacketHandler(PROTOCOL_VERSION)
    

    # Open port
    if portHandler.openPort():
        print("Succeeded to open the port")
    else:
        print("Failed to open the port")
        print("Press any key to terminate...")
        getch()
        quit()
    
    
    # Set port baudrate
    if portHandler.setBaudRate(BAUDRATE):
        print("Succeeded to change the baudrate")
    else:
        print("Failed to change the baudrate")
        print("Press any key to terminate...")
        getch()
        quit()
    
    


    
    while 1:
        time.sleep(0.5)
        dxl_comm_result1, dxl_error1 = packetHandler.write1ByteTxRx(portHandler, DXL1_ID, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)
        dxl_comm_result2, dxl_error2 = packetHandler.write1ByteTxRx(portHandler, DXL2_ID, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)
        dxl_comm_result3, dxl_error3 = packetHandler.write1ByteTxRx(portHandler, DXL3_ID, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)
        dxl_comm_result4, dxl_error4 = packetHandler.write1ByteTxRx(portHandler, DXL4_ID, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)
        dxl_comm_result5, dxl_error5 = packetHandler.write1ByteTxRx(portHandler, DXL5_ID, ADDR_TORQUE_ENABLE, TORQUE_ENABLE)

        print("Press any key to Close...")
        if getch() == chr(0x1b):
            break
        
        time.sleep(0.5)

        dxl_comm_result1, dxl_error1 = packetHandler.write1ByteTxRx(portHandler, DXL1_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
        dxl_comm_result2, dxl_error2 = packetHandler.write1ByteTxRx(portHandler, DXL2_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
        dxl_comm_result3, dxl_error3 = packetHandler.write1ByteTxRx(portHandler, DXL3_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
        dxl_comm_result4, dxl_error4 = packetHandler.write1ByteTxRx(portHandler, DXL4_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
        dxl_comm_result5, dxl_error5 = packetHandler.write1ByteTxRx(portHandler, DXL5_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
        print("Press any key to Open...")

        if getch() == chr(0x1b):
            break


    
    
    if dxl_comm_result1 != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result1))
    elif dxl_error1!= 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error1))
    
    # Close port
    portHandler.closePort()

except KeyboardInterrupt:
   
    # Disable Dynamixel Torque
    dxl_comm_result1, dxl_error1 = packetHandler.write1ByteTxRx(portHandler, DXL1_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result2, dxl_error2 = packetHandler.write1ByteTxRx(portHandler, DXL2_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result3, dxl_error3 = packetHandler.write1ByteTxRx(portHandler, DXL3_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result4, dxl_error4 = packetHandler.write1ByteTxRx(portHandler, DXL4_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result5, dxl_error5 = packetHandler.write1ByteTxRx(portHandler, DXL5_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    
    
    if dxl_comm_result1 != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result1))
    elif dxl_error1!= 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error1))
    
    # Close port
    portHandler.closePort()