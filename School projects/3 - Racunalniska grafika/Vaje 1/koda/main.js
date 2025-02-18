//init
const adapter = await navigator.gpu.requestAdapter();
const device = await adapter.requestDevice();
const canvas = document.querySelector('canvas');
const context = canvas.getContext('webgpu');
const format = navigator.gpu.getPreferredCanvasFormat();
context.configure({ device, format });

//fetch shaders
const code = await fetch('shader.wgsl').then(response => response.text());
const module = device.createShaderModule({ code });

//create pipeline
const pipeline = device.createRenderPipeline({
    vertex: {
        module,
    },
    fragment: {
        module,
        targets: [{ format }],
    },
    layout: 'auto',
});

// encode commands
const commandEncoder = device.createCommandEncoder();

const renderPass = commandEncoder.beginRenderPass({
    colorAttachments: [{
        view: context.getCurrentTexture().createView(),
        loadOp: 'clear',
        clearValue: [0.7, 0.8, 0.9, 1],
        storeOp: 'store',
    }]
});
renderPass.setPipeline(pipeline);
renderPass.draw(6);
renderPass.end();
device.queue.submit([commandEncoder.finish()]);