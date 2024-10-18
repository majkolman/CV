export function multiply(a, b) {
    let a_size = a.length;
    let b_size = b.length;

    let mode;
    //assume matrix is either 4*4 or its a vector length 4
    if(a_size = b_size){
        //matrix * matrix
        mode = 0;
    }else if(a_size > b_size){
        //matrix * vector
        mode = 1;
    }else{
        //vector * matrix
        mode = 2;
    }
    const result = [];
    let mat_size = a.length; 

    switch(mode){
        case 0:
            for(let i = 0; i < mat_size; i++){
                const row = []
                for(let j = 0; j < mat_size; j++){
                    row[j] = 0;
                    for(let k = 0; k < mat_size; k++){
                        row[j] += a[i][k] * b[k][j]
                    }
                }  
                result[i] = row; 
            }
            break;

        case 1:
            for(let i = 0; i < mat_size; i++){
                let mult = 0;
                for(let j = 0; j < mat_size; j++){
                    mult += a[i][j] * b[j];
                }
                result[i] = mult;
            }
            break;

        case 2:
            console.log("Error with multiplication");
            break;
    }
    return result;
}

export function transform(a, v) {
    // IMPLEMENT

}

export function identity() {
    // This is here to demonstrate the matrix format:
    // array of 4 arrays of 4 numbers
    return [
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1],
    ];
}

export function translation(dx, dy, dz) {
    return [
        [1, 0, 0, dx],
        [0, 1, 0, dy],
        [0, 0, 1, dz],
        [0, 0, 0, 1],
    ];
}

export function scale(sx, sy, sz) {
    return [
        [sx, 0, 0, 0],
        [0, sy, 0, 0],
        [0, 0, sz, 0],
        [0, 0, 0, 1],
    ];
}

export function rotationX(angle) {
    let cosa = Math.cos(angle);
    let sina = Math.sin(angle);
    return [
        [1, 0, 0, 0],
        [0, cosa, -sina, 0],
        [0, sina, cosa, 0],
        [0, 0, 0, 1],
    ];
}

export function rotationY(angle) {
    let cosa = Math.cos(angle);
    let sina = Math.sin(angle);
    return [
        [cosa, 0, sina, 0],
        [0, 1, 0, 0],
        [-sina, 0, cosa, 0],
        [0, 0, 0, 1],
    ];
}

export function rotationZ(angle) {
    let cosa = Math.cos(angle);
    let sina = Math.sin(angle);
    return [
        [cosa, -sina, 0, 0],
        [sina, cosa, 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1],
    ];
}

export function perspective(fov, aspect, near, far) {
    // HINT: as in lecture slides, assume d = 1
    let h = 2*Math.tan(fov/2);
    let w = aspect * h;
    return [
        [2/w, 0, 0, 0],
        [0, 2/near, 0, 0],
        [0, 0, far/(near-far), (far*near)/(near-far)],
        [0, 0, -1, 0],
    ];
}

export function viewport(x, y, w, h) {
    // IMPLEMENT
    // HINT: you may have to flip the image upside down,
    // because the Y axis points down on the canvas
}