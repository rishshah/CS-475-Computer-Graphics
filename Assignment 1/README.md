# CS-475 Assignment 1

## Tasks

- Make three models `( laptop, spectacles, bat )` from the code

***

### 1. Modelling Mode [M]

- `[Left Click]` -> Add a point to Model
- `[Shift Left Click]` -> Remove the last added point
- `[K]` -> Save the model created in saved_model.raw
- `[L]` -> Load the model from model.raw
- ensure features to get 3D coordinates

#### Extra Features in Modelling Mode
- `[ Shift Left & {T,G,B} ]` to adjust color of points to add
- `[ Inspection Controls ]` for rotation by 90 degrees to change planes of drawing
- `[W,A,S,D]` for translation in modelling mode to draw in wider space 
- `[R]` for recentering the model
- `[ Shift Left & {Z,X} ]` for moving the plane of modelling by one unit
- `[1,2,3]` for deciding entry mode of points that form triangles
- `[Left-Ctrl]` for displaying current drawing mouse position
-  White point markers for displaying last 2 drawing points
-  Grid display and point snapping for easy drawing
 
***

### 2. Inspection Mode [I] 

- All rotations about centroid
- `[Up/Down]` -> rotate about X axis 
- `[Left/Right]` -> rotate about Y axis
- `[PgUp/PgDown]` -> rotate about Z axis
- `[R]` -> move the origin to centroid of model(?)
- `[W,S,A,D,Z,X]` -> key should allow translation along +ve and -ve Y,X and Z axis respectively

---

## Status

### Timeline 
- Inspection mode all commands 
- Load/Save command done
- File system created
- Mode differenciation
- Managed data strcuture for efficient implementation of modelling part
- Click Input
- Giving features and drawing corresponding to this
- Final Models
	1. Spectacles created
	2. Bat created
	3. Laptop created

***

### In Progress
- Creating 2 structures

---

## Execution

### Compiling
- `cd "Assignment 1"`
- `make`

***

### Testing
- `./executable`

---

## HTML Report
- requires installed doxygen 
- `make report`
- `open in web-browser ./html/index.html`

---

## Clean up
- `make clean`
