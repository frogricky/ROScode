# -*- coding: utf-8 -*-
"""
Created on Fri Oct 13 17:01:30 2023

@author: HungYing
"""

'''
ID4 3100,1050
ID5 2800,1800
ID1 3072,1024
ID2 2000,900
ID3 3000,800
'''


try:

    
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
    
    integers = []
    
    
    
    
    
    
    from dynamixel_sdk import * # Uses Dynamixel SDK library
    
    
    
    ADDR_TORQUE_ENABLE          = 64
    ADDR_GOAL_POSITION          = 116
    ADDR_PRESENT_POSITION       = 132
    DXL_MINIMUM_POSITION_VALUE  = 1         # Refer to the Minimum Position Limit of product eManual
    DXL_MAXIMUM_POSITION_VALUE  = 4094      # Refer to the Maximum Position Limit of product eManual
    BAUDRATE                    = 115200
    
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
    
    
    # Enable Dynamixel Torque
    dxl_comm_result1, dxl_error1 = packetHandler.write1ByteTxRx(portHandler, DXL1_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result2, dxl_error2 = packetHandler.write1ByteTxRx(portHandler, DXL2_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result3, dxl_error3 = packetHandler.write1ByteTxRx(portHandler, DXL2_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result4, dxl_error4 = packetHandler.write1ByteTxRx(portHandler, DXL4_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    dxl_comm_result5, dxl_error5 = packetHandler.write1ByteTxRx(portHandler, DXL5_ID, ADDR_TORQUE_ENABLE, TORQUE_DISABLE)
    
    
    if dxl_comm_result1 != COMM_SUCCESS:
        print("%s" % packetHandler.getTxRxResult(dxl_comm_result1))
    elif dxl_error1 != 0:
        print("%s" % packetHandler.getRxPacketError(dxl_error1))
    else:
        print("Dynamixel has been successfully connected")
    
    
    dxl_present_position1, dxl_comm_result1, dxl_error1 = packetHandler.read4ByteTxRx(portHandler, DXL1_ID, ADDR_PRESENT_POSITION)
    dxl_present_position2, dxl_comm_result2, dxl_error2 = packetHandler.read4ByteTxRx(portHandler, DXL2_ID, ADDR_PRESENT_POSITION)
    dxl_present_position3, dxl_comm_result3, dxl_error3 = packetHandler.read4ByteTxRx(portHandler, DXL3_ID, ADDR_PRESENT_POSITION)
    dxl_present_position4, dxl_comm_result4, dxl_error4 = packetHandler.read4ByteTxRx(portHandler, DXL4_ID, ADDR_PRESENT_POSITION)
    dxl_present_position5, dxl_comm_result5, dxl_error5 = packetHandler.read4ByteTxRx(portHandler, DXL5_ID, ADDR_PRESENT_POSITION)
    
    MX1 = dxl_present_position1
    MX2 = dxl_present_position2
    MX3 = dxl_present_position3
    MX4 = dxl_present_position4
    MX5 = dxl_present_position5
    
    
    while 1:
        # if getch() == chr(0x1b):
        #     break
        
    
        
        
        
         # Read present position
     
        dxl_present_position1, dxl_comm_result1, dxl_error1 = packetHandler.read4ByteTxRx(portHandler, DXL1_ID, ADDR_PRESENT_POSITION)
        dxl_present_position2, dxl_comm_result2, dxl_error2 = packetHandler.read4ByteTxRx(portHandler, DXL2_ID, ADDR_PRESENT_POSITION)
        dxl_present_position3, dxl_comm_result3, dxl_error3 = packetHandler.read4ByteTxRx(portHandler, DXL3_ID, ADDR_PRESENT_POSITION)
        dxl_present_position4, dxl_comm_result4, dxl_error4 = packetHandler.read4ByteTxRx(portHandler, DXL4_ID, ADDR_PRESENT_POSITION)
        dxl_present_position5, dxl_comm_result5, dxl_error5 = packetHandler.read4ByteTxRx(portHandler, DXL5_ID, ADDR_PRESENT_POSITION)
        
        
        
        if (MX1 != dxl_present_position1) or (MX2 != dxl_present_position2) or (MX3 != dxl_present_position3) or (MX4 != dxl_present_position4) or (MX5 != dxl_present_position5):
            print("[ID:%03d] GoalPos:%03d  PresPos:%03d" % (DXL1_ID, dxl_goal_position1[index], dxl_present_position1))
            integers.append(dxl_present_position1)
            print("[ID:%03d] GoalPos:%03d  PresPos:%03d" % (DXL2_ID, dxl_goal_position2[index], dxl_present_position2))
            integers.append(dxl_present_position2)
            print("[ID:%03d] GoalPos:%03d  PresPos:%03d" % (DXL3_ID, dxl_goal_position3[index], dxl_present_position3))
            integers.append(dxl_present_position3)
            print("[ID:%03d] GoalPos:%03d  PresPos:%03d" % (DXL4_ID, dxl_goal_position4[index], dxl_present_position4))
            integers.append(dxl_present_position4)
            print("[ID:%03d] GoalPos:%03d  PresPos:%03d" % (DXL5_ID, dxl_goal_position5[index], dxl_present_position5))
            integers.append(dxl_present_position5)
            print("   ")
    
        
        
        MX1 = dxl_present_position1
        MX2 = dxl_present_position2
        MX3 = dxl_present_position3
        MX4 = dxl_present_position4
        MX5 = dxl_present_position5
        
        
        
        
        if dxl_comm_result1 != COMM_SUCCESS:
            print("%s" % packetHandler.getTxRxResult(dxl_comm_result1))
        elif dxl_error1 != 0:
            print("%s" % packetHandler.getRxPacketError(dxl_error1))
    
        
    
    
    
        # if not abs(dxl_goal_position[index] - dxl_present_position) > DXL_MOVING_STATUS_THRESHOLD:
        #     break
    
        
        
    
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

except KeyboardInterrupt:
    with open("integers.txt", "w") as file:
        file.write("[" + ",".join(map(str, integers)) + "]")
        print("整数已记录并保存到文件 integers.txt")
    
    
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


