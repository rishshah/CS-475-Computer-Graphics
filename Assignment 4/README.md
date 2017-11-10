# CS-475 Assignment 4

## Tasks

- Animate assignment 3 models and scene.

### Models
- Phineas (humainoid)
- Platipus Perry (non humanoid)

### Scene
- Their backyard with grass, compound and sky.

### Keyboard callbacks

- `[ P ]` -> switch to playback mode
- `[ R ]` -> switch to record mode
- `[ V ]` -> switch to view mode ( No models saved in this state )

#### Pan(View) mode
- Just see things from all angles by moving third person camera about its center (but axes of rotation are global axes)

- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rotate about Z axis
- `[ W,S,A,D,Z,X ]` -> keys should allow translation along +ve and -ve Y,X and Z axis respectively

#### Playback Mode
- Play the animation from the one/two keyframes.txt file 

- `[ Q ]` -> Save the animation into a video file
- `[ ... ]` -> Pause the animation at current position (optional)
- `[ ... ]` -> Resume the animation from current position (optional)

#### Record mode
-  Record animation by positioning models using Modelling callbacks and save keyframes when models in right positions

- `[ Q ]` -> Append and save current state into a keyframe
- `[ H ]` -> switch to modelling mode {"phineas"}
- `[ N ]` -> switch to modelling mode {"perry"}
- `[ L ]` -> toggle spotlight from sun shaped sphere

##### Modelling mode for rotating parts about their joins
- `[ Up/Down ]` -> rotate about X axis 
- `[ Left/Right ]` -> rotate about Y axis
- `[ PgUp/PgDown ]` -> rlotate about Z axis

###### Choose Perry parts to model
- `[1]` -> eye_ball_left
- `[2]` -> eye_ball_right
- `[3]` -> lower_mouth
- `[4]` -> tail
- `[5]` -> front_left_leg
- `[6]` -> front_right_leg
- `[7]` -> back_left_leg
- `[8]` -> back_right_leg
- `[9]` -> body

###### Choose Phineas parts to model
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

---

## Status
---

## Execution

### Compiling
- `cd "Assignment 4"`
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

	