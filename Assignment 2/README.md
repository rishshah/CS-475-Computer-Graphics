# CS-475 Assignment 2

## Tasks

- Create a scene using models in assignment 1 and show modelling-viewing pipeline stages.

### Keyboard callbacks [M]

- `[1]` -> WCS to VCS
- `[2]` -> VCS to CCS
- `[3]` -> CCS to NDCS
- `[4]` -> NDCS to DCS
- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rotate about Z axis
- `[ W,S,A,D,Z,X ]` -> key should allow translation along +ve and -ve Y,X and Z axis respectively

---

## Status

### ToDo
- Callbacks need to be added 
- All 4 matrices have to be created
- Clipping algorithm in CCS to be made

### Done
- File structure
- Scene file parsing
- Basic viewing complete
- WCS view
- Callbacks for translation and rotation 

---

## Execution

### Compiling
- `cd "Assignment 2"`
- `make`

### Testing
- `./executable`

### Clean up
- `make clean`

---

## HTML Report
- requires installed doxygen 
- `make report`
- `open in web-browser "./screenshot_page/index.html"`

---

## Refrences
- HTML Report: `https://codyhouse.co/demo/expandable-image-gallery/index.html`
- Callbacks: `http://www.glfw.org/docs/latest/group__keys.html`
- Tutorials: `https://github.com/paragchaudhuri/cs475-tutorials`

	