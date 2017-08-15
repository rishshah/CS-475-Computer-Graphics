# CS-475 Assignment 1

## Tasks

- Make three models `( chair, x, x )` from the code - **Rishabh**

***

##### 1. Modelling Mode [M]

- `[Left Click]` -> Add a point to Model
- `[Shift Left Click]` -> Remove the last added point
- `[K]` -> Save the model created in file.raw
- `[L]` -> Load the model from file.raw
- ensure features to get 3D coordinates

---

##### 2. Inspection Mode [I] 

- All rotations about centroid
- `[Up/Down]` -> rotate about X axis 
- `[Left/Right]` -> rotate about Y axis
- `[PgUp/PgDown]` -> rotate about Z axis
- `[R]` -> move the origin to centroid of model(?)
- `[W,S,A,D,Z,X]` -> key should allow translation along +ve and -ve Y,X and Z axis respectively

#### Progress - **Rishabh**
- Inspection mode all commands done... 
- Load/Save command done
- File system created
- Mode differenciation
- Managed data strcuture for efficient implementation of modelling part

#### ToDo - **Purav**
- Click Input
- Giving features and drawing corresponding to this
- Creating 3 structures accordingly

## Compiling

- `cd "Assignment 1"`
- `make`

## Testing

- `./bin/preview`
