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
- coordinate axes
- VCS changes coordinate instead of moving camera
- Camera never changed ( except from use of keyboard callbacks)
- Flattening in CCS
- Zoom mode Z,X
- NDCS perspective manual division
- DCS has no z coordinate ( camera here has to be changed)

- Clipping algorithm in CCS to be made

### Done
- File structure
- Scene file parsing
- Basic viewing complete
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

	