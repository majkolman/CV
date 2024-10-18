import * as Matrix from './Matrix.js';

export function getForwardTransform({
    translation = [0, 0, 0],
    rotation = [0, 0, 0],
    scale = [1, 1, 1],
} = {}) {
    // IMPLEMENT: construct a matrix that performs transformations in the following order:
    // 1. scale
    // 2. rotate around X axis (angle is given in radians)
    // 3. rotate around Y axis (angle is given in radians)
    // 4. rotate around Z axis (angle is given in radians)
    // 5. translate
    let mat = Matrix.identity();

    let mat_s = Matrix.scale(scale);
    mat = Matrix.multiply(mat_s, mat);

    let mat_rx = Matrix.rotationX(rotation[0]);
    mat = Matrix.multiply(mat_rx, mat);

    let mat_ry = Matrix.rotationX(rotation[1]);
    mat = Matrix.multiply(mat_ry, mat);

    let mat_rz = Matrix.rotationX(rotation[2]);
    mat = Matrix.multiply(mat_rz, mat);

    let mat_t = Matrix.translation(translation);
    mat = Matrix.multiply(mat_t, mat);

    return mat;
}

export function getInverseTransform({
    translation = [0, 0, 0],
    rotation = [0, 0, 0],
    scale = [1, 1, 1],
} = {}) {
    // IMPLEMENT: construct an inverse matrix to the above operations
    // IMPORTANT: do not write a general matrix inverse method, because it is
    // incredibly computationally expensive -- be smarter than that
    let mat = Matrix.identity();

    let mat_t = Matrix.translation(-translation[0], -translation[1], -translation[2]);
    mat = Matrix.multiply(mat_t, mat);

    let mat_rz = Matrix.rotationX(-rotation[2]);
    mat = Matrix.multiply(mat_rz, mat);

    let mat_ry = Matrix.rotationX(-rotation[1]);
    mat = Matrix.multiply(mat_ry, mat);

    let mat_rx = Matrix.rotationX(-rotation[0]);
    mat = Matrix.multiply(mat_rx, mat);

    let mat_s = Matrix.scale(-scale[0], -scale[1], -scale[2]);
    mat = Matrix.multiply(mat_s, mat);
    
    return mat;
}
