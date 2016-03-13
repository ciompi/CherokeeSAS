#include "RTIMULib.h"
#include "rpiServo.h"

int main()
{
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;
    int YawRateGain = 0.1;

    //  Using RTIMULib here allows it to use the .ini file generated by RTIMULibDemo.
    //  Or, you can create the .ini in some other directory by using:
    //      RTIMUSettings *settings = new RTIMUSettings("<directory path>", "RTIMULib");
    //  where <directory path> is the path to where the .ini file is to be loaded/saved

    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    RTIMU *imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("Canny find the IMU ya dafty.\n");
        exit(1);
    }

    //  This is an opportunity to manually override any settings before the call IMUInit

    //  set up IMU

    imu->IMUInit();

    //  this is a convenient place to change fusion parameters

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    //  set up for rate timer

    rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();

    //  now just process data

    while (1) {
        //  poll at the rate recommended by the IMU

        usleep(imu->IMUGetPollInterval() * 1000);

        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
            sampleCount++;

            now = RTMath::currentUSecsSinceEpoch();

            //  display 10 times per second

            if ((now - displayTimer) > 100000) {
              // for testing comment out unused lines and change \n for \r,
              //printf("Observer Orientation Output. Roll: %.2f [deg] Pitch: %.2f [deg] Yaw: %.2f [deg]\n", (180/3.14)*imuData.fusionPose.x(),(180/3.14)*imuData.fusionPose.y(),(180/3.14)*imuData.fusionPose.z());
              //printf("Gryo Output. Roll Rate: %.2f [deg/s] Pitch Rate: %.2f [deg/s] Yaw Rate: %.2f [deg/s]\n", (180/3.14)*imuData.gyro.x(),(180/3.14)*imuData.gyro.y(),(180/3.14)*imuData.gyro.z());
              //printf("Accelerometer. X: %.2f [m/s^2] Y: %.2f [m/s^2] X: %.2f [m/s^2]\n", (9.81)*imuData.accel.x(),(9.81)*imuData.accel.y(),(9.81)*imuData.accel.z());
              servo.setAngle(-YawRateGain*(180/3.14)*imuData.gyro.x());
              fflush(stdout);
              displayTimer = now;
            }

            //  update rate every second

            if ((now - rateTimer) > 1000000) {
                sampleRate = sampleCount;
                sampleCount = 0;
                rateTimer = now;
            }
        }
    }
}
