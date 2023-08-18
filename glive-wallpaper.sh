#!/usr/bin/bash

# Prompt the user to enter the path to the image file
read -p "Enter the path to the gif file: " image_path

# Check if the file exists
if [ ! -f "$image_path" ]; then
	echo "Error: File not found!"
	exit 1
#else
	# Save the variable
fi

# Get amount of frames for later use
frame_amount=$(exiftool -b -FrameCount $image_path)
echo "The file has $frame_amount frames."

# Convert the image to frames with imagemagick
convert -coalesce "$image_path" frames/frame.png
echo "Image converted to frames succesfully."

# Disable animations so there is no blur
gsettings set org.gnome.desktop.interface enable-animations false

# Change theme to light because the background is changed only for light theme?
# gsettings set org.gnome.shell.ubuntu color-scheme prefer-light

# Set the background to a frame every 0.2 seconds
# Maybe save the necessary variables to a file and move this part to a different script, so what is left here would be the set up script.


typeset -i num
num=0
while true
do
	if [ "$frame_amount" -gt "$num" ]; then
		gsettings set org.gnome.desktop.background picture-uri file://${PWD}/frames/frame-$num.png
		echo "file://${PWD}/frames/frame-$num.png"
		echo "Tried to set wallpaper."
		num=$(( $num + 1 ))
	else
		num=0
	fi
	sleep 0.3
done

#while true
#do
#	typeset -i num
#	num=0
#	while [ "$frame_amount" -gt "$num" ]
#	do
#		gsettings set org.gnome.desktop.background picture-uri file://${PWD}/frames/frame-$num.png
#		echo "file://${PWD}/frames/frame-$num.png"
#		echo "Tried to set wallpaper."
#		num=$(( $num + 1 ))
#
#		sleep 0.1
#	done
#done
