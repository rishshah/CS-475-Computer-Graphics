# CS-475 Assignment 2

## Tasks

- Create a scene using models in assignment 1 and show modelling-viewing pipeline stages.

***

### 1. Keyboard callbacks [M]

- `[1]` -> WCS to VCS
- `[2]` -> VCS to CCS
- `[3]` -> CCS to NDCS
- `[4]` -> NDCS to DCS
- `[ W,S,A,D,Z,X ]` -> key should allow translation along +ve and -ve Y,X and Z axis respectively

---

## Status

### ToDo
- Callbacks need to be added 
- Camera setup needed in basic viewing
- All 4 matrices have to be created
- Clipping algorithm in CCS to be made

***

### Done
- File structure created
- Scene file parsed
- Basic viewing complete

---

## Execution

### Compiling
- `cd "Assignment 2"`
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

	