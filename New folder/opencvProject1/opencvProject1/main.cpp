#include<iostream>  
#include<opencv2/opencv.hpp>  
using namespace std;  
using namespace cv;  

int main() {  
    // Open the video file or camera  
    VideoCapture cap("C:\\Users\\bhard\\Downloads\\videoplayback.webm");
    // Correct the string literal by using single quotes for the path and escaping backslashes properly  

    if (!cap.isOpened()) {  
        cout << "Error: Could not open video." << endl;  
        return -1;  
    }  

    CascadeClassifier body_cascade;  
    if (!body_cascade.load("C:\\Users\\bhard\\Desktop\\New folder\\opencvProject1\\x64\\Release\\haarcascade_frontalface_default.xml")) {  
        cout << "Error: Could not load cascade classifier." << endl;  
        return -1;  
    }  

    // Create a full screen window  
    namedWindow("Person Detection", WINDOW_NORMAL);  
    setWindowProperty("Person Detection", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);  

    Mat frame, gray;  
    long long totalPersons = 0; // Accumulate total persons detected  
    int frameCount = 0;         // Count frames processed  

    // Process video frames in a loop  
    while (true) {  
        if (!cap.read(frame) || frame.empty()) {  
            cout << "End of video or cannot read the frame." << endl;  
            break;  
        }  

        cvtColor(frame, gray, COLOR_BGR2GRAY);  
        vector<Rect> persons;  
        // Detect people in the resized frame  
        body_cascade.detectMultiScale(gray, persons, 1.1, 3);  

        // Draw rectangles around detected persons  
        for (size_t i = 0; i < persons.size(); i++) {  
            rectangle(frame, persons[i], Scalar(0, 255, 0), 2);  
        }  

        // Show count on frame  
        putText(frame, "Persons: " + to_string(persons.size()), Point(10, 30),  
                FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);  

        imshow("Person Detection", frame);  

        // Print count to console  

        cout << "Persons detected: " << persons.size() << endl;  

        // Accumulate total persons and frame count  
        totalPersons += persons.size();  
        frameCount++;  

        if (waitKey(30) == 27) break; // Exit on ESC key  
    }  

    cap.release();  
    destroyAllWindows();  

    // Print total sum and average  
    cout << "Total persons detected (sum over all frames): " << totalPersons << endl;  
    if (frameCount > 0)  
        cout << "Average persons per frame: " << static_cast<double>(totalPersons) / frameCount << endl;  

    return 0;  
}