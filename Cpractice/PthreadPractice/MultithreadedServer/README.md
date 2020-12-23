# Multithreading server via sockets and pthread

# Description
## This is multithreading server that accepts clients, which send to server file paths of file to read. Server reads the contents of file and sends it back to client. **Actually, the model is insecure, as clients can read any file that they want, but this is just for practice, not more.**

# HOW TO USE
## First launch server
  ### dmkrch: ./multithreadingServer
## Then launch clients, passing to their arguments fulll path to file
  ### dmkrch: ./clientMultithreadingServer /home/dmkrch/.../test.txt
## After that, if everyting was fine, client returns data of file to client, that will be printed to client stdout