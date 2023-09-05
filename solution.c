#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

struct VehiclePosition {
    int32_t  Id; // 32 bit int Position Id
    char VehicleReg[256]; // ASCII String Vehicle Registration
    float Latitude; // 32 bit Floating point Latitude
    float Longitude; // 32 bit Floating point Longitude
    uint64_t Timestamp;// 64 bit int Timestamp
}; // define structure of the Binary file containing the 2 million vehicle positions

float DistanceCalc(float Latitude1, float Longitude1, float Latitude2, float Longitude2) {
    float deltaLat = (Latitude1 - Latitude2); // latitude difference
    float deltaLon = (Longitude1 - Longitude2);// Longitude difference
    float result = sqrt(pow(deltaLat,2) + pow(deltaLon,2)); // distance
    return result;
}; // This function calculates the distance between 2 co-ordinates using the Euclidean method.

int main() {
    // variables
    int itr = 0; // troubleshoot flow control.
    clock_t start_time = clock(); // record the time the program started running 
    clock_t end_time;
    float total_time;
    float co_ordinates[10][2] = {
        {34.544909, -102.100843},
        {32.345544, -99.123124},
        {33.234235, -100.214124},
        {35.195739, -95.348899},
        {31.895839, -97.789573},
        {32.895839, -101.789573},
        {34.115839, -100.225732},
        {32.335839, -99.992232},
        {33.535339, -94.792232},
        {32.234235, -100.222222},
    }; // Define the 2D array which contains the reference positions.

    FILE *filename; // Define the variable file as a File.
    
    
    for (int n = 0; n < 10; n++) {
        int PostionId = -1;
        float StoredDist = -1;
        struct VehiclePosition position; // buffer where data is to be stored
        filename = fopen("VehiclePositions.dat", "rb"); // Open the binary file using the rb method.

        if (filename == NULL) {
            return 1;
        } // Check to see if file exists

        while (fread(&position, sizeof(struct VehiclePosition), 1, filename) == 1) {
            float distance = DistanceCalc(co_ordinates[n][0], co_ordinates[n][1],position.Latitude, position.Longitude);
            if (StoredDist == -1 || distance < StoredDist) {
                StoredDist = distance;
                PostionId = position.Id;
            } // Check if new distance less than previous 
        } // Loop through each Vehicle position to find closest position.

        printf("For Co-ordinate %d, Closest Vehicle at Position Id  %d\n", n + 1,PostionId); // Echo the resulting Postion Id
        fclose(filename); // Close the binary file

    }// loop through the each of the coodinates to find vehicle which is closest to its position
    
    end_time = clock(); 
    total_time = ((float)(end_time - start_time));
    printf("Execution time= %.1f ms\n", total_time);
    return 0;
}
