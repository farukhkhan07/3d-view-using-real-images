# 3d-view-using-real-images
 # Requirement Analysis
 
# 2.1 Software Requirements
	•	Windows XP or a higher version (operating system).
	•	Microsoft Visual Studio 2010 or a higher version.
# 2.2 Hardware Requirements
	•	Pentium dual core or new updated hardware.
	•	Graphics card with 256 MB VRAM and Pixel Model 3.0 of hardware support.
	•	1 GB RAM or higher.
	•	Peripheral devices like cameras or smart phone cameras, mice, keyboards etc.
# 2.3 Tool and Technologies
	•	Microsoft Visual Studio 2010 or a higher version.
(Microsoft Visual Studio is the integrated development environment in which different libraries are added.)
	•	OPEN CV with C++ interface configured in Microsoft Visual Studio.
(OPEN CV is a tool to develop 3D Models and is configured in Microsoft Visual Studio.)

# Implementation 
# 5.1 Pair Saving
• In pair saving, stereo cameras are placed in particular positions. This method helps to get the mixed results of both cameras. “Addweighted” function of Open CV is used to get the mixed result. 
• Note: For taking the images, we use “space bar”.
# 5.1.1 “Addweighted” function:
The “addweighted” function is used to determine the sum of the two arrays. It is used to check the position level of the cameras C++ format: void adwghtd   (ip array sr1,d.alp,ip array sr2,d.bet, d.gma,op.arraydst,int m typ 2)
# 5.1.2 Parameters:
Following are the seven parameters of the “addweighted” function:

a. Input Source Array 1: It is the first input of the camera.

b. Alpha: It is used for the weight of first array elements.

c. Input Source Array 2: It is the second input of the camera.

d. Beta: It is used for the weight of second array elements.

e. Gamma: It is a scalar which is added to each and every sum.

f. dst: It is an output array which has the same size and the number of channels.

g. (d type):When both the arrays have the same depth then it is an optional method. Addweighted calculates the sum of the two arrays by using the following equation:

d (m) = sat ( sr1 (m) * alp+ sr2 (m)* bet+ gam)

# Where:
d is destination.

sat is saturate.

sr is source.

alp is alpha.

bet is beta.

gam is gamma.


# 2 Calibration
After taking the left and right pictures in the pair saving, the step of calibration is to cross-check the intrinsic and extrinsic values of the camera. The extrinsic and intrinsic values of cameras give us the following XML and YML files.

	•	Distortion coefficient of camera 1
	•	Distortion coefficient of camera 2
	•	Camera Matrix 1
	•	Camera Matrix 2
	•	Map of X and Y of camera 1
	•	Map of X and Y of camera 2
	•	Rotation of camera 1
	•	Rotation of camera 2
	•	Translation
	•	Q Matrix
	•	Distortion Coefficient:The distortion coefficient is same as the camera resolution. These resolutions are scaled next to the existing resolutionfrom the resolutionwhich is calibrated. Distortion Coefficients = (a1 a2 b1 b2a3)
	•	Camera Matrix: If we want additional information about intrinsic and extrinsicparameters, camera matrix is desired. It includes focal length (fs,fe) and the optical centers (Cz,Cr).
	•	Rotation:Rotation is linear transformation .It is used to rotate the image. We can also generate the rotation matrix. 
	It includes two things.
	
	•	The center where the image rotates.
	•	The angle which have to be rotated. 
	•	Translation:Translation is a vector addition. It moves a vector to a certain distancein a certain direction.



