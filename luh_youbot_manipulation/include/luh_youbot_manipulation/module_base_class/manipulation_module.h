/* *****************************************************************
 *
 * luh_youbot_manipulation
 *
 * Copyright (c) 2015,
 * Institute of Mechatronic Systems,
 * Leibniz Universitaet Hannover.
 * (BSD License)
 * All rights reserved.
 *
 * http://www.imes.uni-hannover.de
 *
 * This software is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.
 *
 * For further information see http://www.linfo.org/bsdlicense.html
 *
 * Author: Simon Aden (simon.aden@mailbox.org)
 ******************************************************************/

#ifndef LUH_YOUBOT_MANIPULATION_MANIPULATION_MODULE_H
#define LUH_YOUBOT_MANIPULATION_MANIPULATION_MODULE_H

#include "ros/ros.h"
#include "brics_actuator/JointPositions.h"
#include "brics_actuator/JointVelocities.h"
#include "brics_actuator/JointAccelerations.h"
#include "brics_actuator/JointTorques.h"
#include "luh_youbot_kinematics/arm_kinematics.h"
#include "sensor_msgs/JointState.h"
#include "tf/transform_listener.h"
#include "luh_youbot_interface/youbot_interface.h"
#include <luh_youbot_poses/youbot_poses.h>

class ManipulationModule
{
public:
    ManipulationModule();

    enum ModuleStatus
    {
        STATUS_FAILURE,
        STATUS_ACTIVE,
        STATUS_IDLE
    };

    // virtual methods that have to be implemented
    virtual void deactivate() = 0; // deactivates the module
    virtual void activate() = 0; // activates the module
    virtual void update() = 0; // updates the module and sets the commands
    virtual void init() = 0; // initialisation
    virtual void emergencyStop() = 0; // this should abort all actions but don't set any commands

    // methods implemented in base class
    ModuleStatus getStatus(){return status_;}

    static void initStatic(ros::NodeHandle *node, tf::TransformListener &tf_listener, YoubotInterface *youbot);

    static void setArmUpdateFrequency(double frequency);
    static void setBaseUpdateFrequency(double frequency);

    static bool isArmBusy();
    static bool isBaseBusy();
    static bool isGripperBusy();
    static void setArmIsBusy(bool arm_is_busy);
    static void setBaseIsBusy(bool base_is_busy);
    static void setGripperIsBusy(bool gripper_is_busy);

protected:

    static bool arm_is_busy_;
    static bool base_is_busy_;
    static bool gripper_is_busy_;

    static bool is_initialised_;

    static ros::NodeHandle* node_;

    static double arm_update_frequency_;
    static double base_update_frequency_;

    static tf::TransformListener* tf_listener_;

    static YoubotInterface* youbot_;

    static youbot_poses::PoseMap predefined_poses_;

    ModuleStatus status_;
};

#endif // MANIPULATION_MODULE_H