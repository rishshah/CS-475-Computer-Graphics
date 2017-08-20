# CS-475 Assignment 1

## Tasks

- Make three models `( laptop, lighthouse, bat )` from the code

***
### 1. Modelling Mode [M]

- `[Left Click]` -> Add a point to Model
- `[Shift Left Click]` -> Remove the last added point
- `[K]` -> Save the model created in file.raw
- `[L]` -> Load the model from file.raw
- ensure features to get 3D coordinates

#### Features to add points in Modelling Mode
- `[ Shift Left & {T,G,B} ]` to adjust color of points to add
-  Rotation by 90 degrees to change planes of drawing
- `[ Shift Left & {Z,X} ]` for moving the plane of modelling by one unit
- `[1,2,3]` for deciding entry mode of points that form triangles
- `[Left-Ctrl]` for displaying current drawing position
-  White point markers for displaying last 2 drawing points

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
-- Spectacles created
-- Bat created
-- Laptop created

### In Progress
- Creating 2 structures

---
## Execution

### Compiling
- `cd "Assignment 1"`
- `make`

### Testing
- `./executable`

---
## HTML Report
- `cd "Assignment 1"`
- `doxygen config_file`
- `open in web-browser ./html/index.html`

## Clean up
- `make clean`
