# JPG-to-ASCII
Converts a JPG to ASCII text art

Not complete. I got bored memorizing lines for a play and wanted to see how well this would work.

Gross code but kind of fun. I will come back to this.

##Tested on Ubuntu 14.04 with OpenCV 3.0

#Build steps
##Typical CMake build
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`

#Running it
I provided you with a sample image to test it on :smirk:

1. `cd build`
2. `./JPG-to-ASCII ../resources/MontagueHeadshot.jpg`

#Viewing your ASCII art
Here is an example. I used gedit to view the image but I had to make two changes:

1. Disable text wrapping
  * Edit->Preferences->View
  * Under **Text Wrapping** uncheck the **Enable text wrapping** radio box
2. Enable text resizing
  * I followed this [link](http://askubuntu.com/questions/409630/how-can-i-get-plugins-for-gedit-for-zooming-the-text-file)

##After those changes...

1. `cd build`
2. `gedit Output.txt`

