1. To run DAQ: 32rf95 is a firmware for end-node, while Gateway for firmware at Raspberry 
and LoRaReceiver for base station
2. To run Kalman filter: run kalmanFilter.ipynb using jupyter notebook, 
then config the csv filet at variable data1 anda data2
3. To run Trilateration: coord csv is a point position based on kalman filter, and draw.py is for
setting up translation position from x,y to coord position, main.py is the main program that should run with python main.py
4. To run RMSE: config the csv file from trilateration at variable file, and run rmseValidation.ipynb using jupyter notebook