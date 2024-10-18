import * as Matrix from './Matrix.js';
import * as Transform from './Transform.js';

export class Renderer {

    constructor(context) {
        this.context = context;
    }

    render(camera, model) {
        const { width, height } = this.context.canvas;
        this.context.clearRect(0, 0, width, height);

        // IMPLEMENT: transform all vertices (object -> world -> clip -> ndc -> viewport)
        // HINT: this cannot be done with a single matrix

        /*
        let obj_wrld = Transform.getForwardTransform(model.transform);
        let wrld_clip = Transform.getInverseTransform(camera.transform);
        let clip_ndc = Matrix.perspective(camera.fov, camera.aspect, camera.near, camera.far);

        let final_transform = Matrix.multiply(wrld_clip, obj_wrld);
        final_transform = Matrix.multiply(clip_ndc, final_transform);
        
        
        for(let i = 0; i < model.vertices; i++){
            model.vertices[i] = Matrix.multiply(final_transform, model.vertices[i]);
        }
        */

        // IMPLEMENT: render the transformed geometry
        // 1. loop over indices
        // 2. discard triangles facing away from the camera
        // 3. draw remaining triangles    

        
        for(let i = 0; i < model.indices.length; i++){
            this.drawTriangle(model.indices[0],model.indices[1],model.indices[2]);
        }
        

    }

    // Draws a triangle in viewport coordinates
    drawTriangle(v0, v1, v2) {
        this.context.beginPath();
        this.context.moveTo(...v0);
        this.context.lineTo(...v1);
        this.context.lineTo(...v2);
        this.context.closePath();
        this.context.stroke();
    }

}
