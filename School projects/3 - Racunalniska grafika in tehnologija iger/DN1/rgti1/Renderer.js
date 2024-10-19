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

        let obj_wrld = Transform.getForwardTransform(model.transform);
        let wrld_clip = Transform.getInverseTransform(camera.transform);
        let clip_ndc = Matrix.perspective(camera.fov, camera.aspect, camera.near, camera.far);

        let final_transform = Matrix.multiply(wrld_clip, obj_wrld);
        final_transform = Matrix.multiply(clip_ndc, final_transform);

        for(let vertex of model.vertices){
            vertex = Matrix.multiply(final_transform, vertex);

            // NOT WORKING --- FIX
            let w = vertex[3];
            vertex = vertex.map(coord => coord / w);
            console.log(vertex[3]); 

            // Transform NDC to viewport coordinates
            vertex = Matrix.multiply(
                Matrix.viewport(0, 0, width, height), // NDC -> viewport (screen space)
                vertex
            );
        }


        // IMPLEMENT: render the transformed geometry
        // 1. loop over indices
        // 2. discard triangles facing away from the camera
        // 3. draw remaining triangles    

        
        
        
        
        for(let index of model.indices){
            let v0 = model.vertices[index[0]];
            let v1 = model.vertices[index[1]];
            let v2 = model.vertices[index[2]];
            this.drawTriangle(v0, v1, v2);
        }
        

    }

    // Draws a triangle in viewport coordinates
    drawTriangle(v0, v1, v2) {
        console.log(v0 + " " + v1 + " " + v2);
        this.context.beginPath();
        this.context.moveTo(...v0);
        this.context.lineTo(...v1);
        this.context.lineTo(...v2);
        this.context.closePath();
        this.context.stroke();
    }

}
