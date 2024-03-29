# CS-475 Assignment 3

## Tasks

- Model one humanoid and one non humanoid character.
- Use key callbacks to do heirarchical modelling
- Create a scene with lighting, texture and place models in that scene

### Models
- Phineas (humainoid)
- Platipus Perry (non humanoid)

### Scene
- Their backyard with grass, compound and sky.

### Keyboard callbacks

- `[ P ]` -> switch to pan mode
- `[ H ]` -> switch to modelling mode {"phineas"}
- `[ N ]` -> switch to modelling mode {"perry"}
- `[ L ]` -> toggle spotlight from sun shaped sphere

#### Modelling mode for rotating parts about their joins
- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rlotate about Z axis

##### Choose Perry parts to model
- `[1]` -> eye_ball_left
- `[2]` -> eye_ball_right
- `[3]` -> lower_mouth
- `[4]` -> tail
- `[5]` -> front_left_leg
- `[6]` -> front_right_leg
- `[7]` -> back_left_leg
- `[8]` -> back_right_leg
- `[9]` -> body

##### Choose Phineas parts to model
- `[1]` -> face
- `[2]` -> sleeve_left
- `[3]` -> sleeve_right
- `[4]` -> hand_left
- `[5]` -> hand_right
- `[6]` -> thigh_left
- `[7]` -> thigh_right
- `[8]` -> leg_left
- `[9]` -> leg_right
- `[0]` -> body

#### Pan mode moving third person camera about its center (but axes of rotation are global axes)
- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rotate about Z axis
- `[ W,S,A,D,Z,X ]` -> keys should allow translation along +ve and -ve Y,X and Z axis respectively

---

## Timeline
- Made file structure, classes to make easy hierarchial modelling 
- Make models' parts; save them in file with their joint information
- Perry model created
- Phineas model created
- Create sceen as a fixed joint model
- Search and apply correct textures to scene and perry
- Create callbacks creatively so as to reuse most of them as there could be many such ones
- Assemble models and animate them
- rotating sky created
- 3 Lightings ( 2 directional and 1 point source (spot light out of sun))
- Placment of models in sceen finally

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

	