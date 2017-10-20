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
- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rotate about Z axis
- `[ W,S,A,D,Z,X ]` -> In nonscaling mode, key should allow translation along +ve and -ve Y,X and Z axis respectively
- `[ W,S,A,D,Z,X ]` -> In scaling mode, key should allow scaling along Y,X and Z axis respectively
- `[ C ]` -> Toggle scaling mode.
- `[ L ]` -> Enter name of heirarchical model relative to FILENAME variable and without extensions to load in the scene
- `[ P ]` -> navigate in pan mode
- `[ Q ]` -> select model index (in model list stored in scene) to apply changes on (feature in progress default 0) and swirch out of pan mode
---

## Status
- Made file structure, classes to make easy hierarchial modelling 
- Make models' parts; save them in file with their joint information
- Interactive view to create heirarchical models created
- Perry model created

### ToDo
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

	