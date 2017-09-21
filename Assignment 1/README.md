# CS-475 Assignment 1

## Tasks

- Make three models `( umbrella, spectacles, cricket_bat )` in the designed modelling mode

***

### 1. Modelling Mode [M]

- `[ Left Click ]` -> Add a point to Model
- `[ Shift Left Click ]` -> Remove the last added point
- `[ K ]` -> Save the model
- `[ L ]` -> Load the model
- Note to load a different model change `line number 9` in `"./modelling/render.cpp"` appropriately

#### Extra Features in Modelling Mode
- `[ Shift Left & {R,G,B} and {T,H,N} ]` to adjust color of points to add
- `[ Inspection Controls ]` for rotation by 90 degrees to change planes of drawing
- `[ W,A,S,D ]` for translation in modelling mode to draw in wider space 
- `[ Shift Left & {Z,X} ]` for moving the plane of modelling by one unit in viewing axis
- `[ 1,2,3 ]` for deciding entry mode of points that form triangles
- `[ Left-Ctrl ]` for displaying current drawing mouse position
-  Colored point markers for displaying last 2 drawing points
-  Grid display and point snapping for easy drawing
 
***

### 2. Inspection Mode [I] 

- All rotations about centroid
- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rotate about Z axis
- `[ R ]` -> move the origin to centroid of model(?)
- `[ W,S,A,D,Z,X ]` -> key should allow translation along +ve and -ve Y,X and Z axis respectively

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
- Final Models and debugging
	1. Spectacles created
	2. Bat created
	3. Umbrella created

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
- `open in web-browser "./screenshot_page/index.html"`

---

## Clean up
- `make clean`

## Refrences
- HTML Report: `https://codyhouse.co/demo/expandable-image-gallery/index.html`
- Callbacks: `http://www.glfw.org/docs/latest/group__keys.html`
- Tutorials: `https://github.com/paragchaudhuri/cs475-tutorials`

	