# CS-475 Assignment 3

## Tasks

- Model one humanoid and one non humanoid character.
- Use key callbacks to do heirarchical modelling
- Create a scene with lighting, texture and place models in that scene

### Models
- Phineas 
- Platipus Perry

### Scene
- Their backyard with grass, compound one or two trees.
- Lighting yet to be decided....

### Keyboard callbacks
- `[0,1,2,3,4]` -> select model index (in model list stored in scene) to apply changes on (feature in progress default 0)

- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rotate about Z axis
- `[ W,S,A,D,Z,X ]` -> In nonscaling mode, key should allow translation along +ve and -ve Y,X and Z axis respectively
- `[ W,S,A,D,Z,X ]` -> In scaling mode, key should allow scaling along Y,X and Z axis respectively
- `[ C ]` -> Enter and exit scaling mode.
- `[ L ]` -> Enter name of model relative to ./models/ and without extension. This heirarchical model is loaded in scene.
- `[ k ]` -> Save a particular heirarchical model of scene

---

## Status
- File structure in progress
- Class structure completed
- Most of the interactive view to create heirarchical models created

### ToDo
- Make file structure, classes to make easy hierarchial modelling 
- Make models' parts; save them in file with their joint information
- Create code to join models based on joint information
- Create sceen as a fixed joint model
- Search and apply correct textures to objects
- Create callbacks creatively so as to reuse most of them as there could be many such ones
- Assemble models and animate them

---

## Execution

### Compiling
- `cd "Assignment 3"`
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

	