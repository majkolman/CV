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

        const obj_wrld = Transform.getForwardTransform(model.transform);
        const wrld_clip = Transform.getInverseTransform(camera.transform);
        const clip_ndc = Matrix.perspective(camera.fov, width/height, camera.near, camera.far);

        const final_transform = Matrix.multiply(clip_ndc, Matrix.multiply(wrld_clip, obj_wrld));
        const viewport = Matrix.viewport(0, 0, width, height);


        const transformed_vertices = model.vertices.map(vertex => {
            //add w coord
            const vertex_plus_w = [...vertex, 1];
            //transform
            let transformed_vertex = Matrix.multiply(final_transform, vertex_plus_w);
            //correct for w
            let w = transformed_vertex[3];
            transformed_vertex = transformed_vertex.map(coord => coord / w);
            //transform with viewport
            transformed_vertex = Matrix.multiply(viewport, transformed_vertex);
            //remove w
            return transformed_vertex.slice(0, 3);
        });

        // IMPLEMENT: render the transformed geometry
        // 1. loop over indices
        // 2. discard triangles facing away from the camera
        // 3. draw remaining triangles    

        for(let index of model.indices){
            let v0 = transformed_vertices[index[0]];
            let v1 = transformed_vertices[index[1]];
            let v2 = transformed_vertices[index[2]];

            //calculate normal of triangle
            let e1 = [v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2]];
            let e2 = [v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2]];
            /*
                //cross product
            let normal = [
                e1[1] * e2[2] - e1[2] * e2[1],
                e1[2] * e2[0] - e1[0] * e2[2],
                e1[0] * e2[1] - e1[1] * e2[0],
            ];
            */
            //check if facing toward camera
            let camera = [0,0,1];
            //camera = [0,0,1] so only z coordinate matters in dot product
            if((e1[0] * e2[1] - e1[1] * e2[0]) < 0) this.drawTriangle(v0, v1, v2);
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
