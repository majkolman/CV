export class Animator {

    constructor() {
        // HINT: you may want to attach your event listeners here
        this.keys = {};
        this.rotation_speed = 0.02;

        window.addEventListener("keydown", (event) => this.onKeyDown(event));
        window.addEventListener("keyup", (event) => this.onKeyUp(event));
    }

    onKeyDown(event) {
        this.keys[event.key] = true;
    }

    onKeyUp(event) {
        this.keys[event.key] = false;
    }

    animate(camera, model) {
        // IMPLEMENT: interaction (mouse, keyboard ... your choice)
        if(this.keys["w"])model.transform.rotation[0] = (model.transform.rotation[0] - this.rotation_speed) % 360;
        if(this.keys["s"])model.transform.rotation[0] = (model.transform.rotation[0] + this.rotation_speed) % 360;
        if(this.keys["a"])model.transform.rotation[1] = (model.transform.rotation[1] - this.rotation_speed) % 360;
        if(this.keys["d"])model.transform.rotation[1] = (model.transform.rotation[1] + this.rotation_speed) % 360;

        if(this.keys["g"])model.transform.scale = model.transform.scale.map(scale => scale + this.rotation_speed);
        if(this.keys["f"])model.transform.scale = model.transform.scale.map(scale => scale - this.rotation_speed);
        /*
        model.transform.rotation[1] = (model.transform.rotation[1] + 0.01) % 360;
        model.transform.rotation[2] = (model.transform.rotation[2] + 0.01) % 360;
        */
    }

}
/*
const camera = {
    transform: {
        translation: [0, 0, 5],
        rotation: [0, 0, 0],
    },
    fov: 1,
    near: 0.01,
    far: 100,
};

const model = {
    transform: {
        translation: [0, 0, 0],
        rotation: [0, 0, 0],
        scale: [1, 1, 1],
    },
    vertices: [],
    indices: [],
};
*/
