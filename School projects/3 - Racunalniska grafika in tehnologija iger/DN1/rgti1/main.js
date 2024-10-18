// !!! You should not edit this file !!!

import { parseOBJ } from './OBJ.js';
import { Renderer } from './Renderer.js';
import { Animator } from './Animator.js';

// Initialize context and renderer
const canvas = document.querySelector('canvas');
const renderer = new Renderer(canvas.getContext('2d'));
const animator = new Animator();

// Camera and model are just plain objects
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

// This is the "main" function, it is called every frame
function frame() {
    // Resize canvas to CSS size
    const { width, height } = canvas.getBoundingClientRect();
    Object.assign(canvas, { width, height });

    // Animate the model (including user interaction)
    animator.animate(camera, model);

    // Render the model
    renderer.render(camera, model);

    // Request next frame
    requestAnimationFrame(frame);
}
requestAnimationFrame(frame);

// Enable drag-and-drop of OBJ and JSON files
canvas.addEventListener('drop', async e => {
    // Prevent the browser from opening the file
    e.preventDefault();
    // Get all dragged files as File objects
    const draggedFiles = [...e.dataTransfer.items]
        .filter(({ kind }) => kind === 'file')
        .map(item => item.getAsFile());

    // Parse files with extensions .obj or .json
    for (const file of draggedFiles) {
        const fileExt = file.name.toLowerCase().split('.').pop();

        if (fileExt === 'obj') {
            const text = await file.text();
            Object.assign(model, parseOBJ(text));
        } else if (fileExt === 'json') {
            const text = await file.text();
            const json = JSON.parse(text);
            Object.assign(camera, json.camera);
            Object.assign(model, json.model);
        }
    }
});

// Prevent the browser from opening the file
canvas.addEventListener('dragover', e => {
    e.preventDefault();
});
