// !!! You should not edit this file !!!

function triangulate(list) {
    // This is similar to OpenGL's TRIANGLE_FAN mode
    const triangles = [];
    for (let i = 2; i < list.length; i++) {
        triangles.push([list[0], list[i - 1], list[i]]);
    }
    return triangles;
}

export function parseOBJ(text) {
    const lines = text.split('\n');

    // v <x> <y> <z>
    const vertices = lines
        .filter(line => /v\s.*/.test(line))
        .map(line => [...line.match(/v\s+(\S+)\s+(\S+)\s+(\S+)\s*/)].slice(1))
        .map(entry => entry.map(entry => Number(entry)));

    // f <v/t/n> <v/t/n> <v/t/n> ...
    const indices = lines
        .filter(line => /f\s.*/.test(line))
        .map(line => line.slice(1).trim().split(/\s+/)
            .map(spec => spec.match(/(\d+).*/)[1])
            .map(entry => Number(entry) - 1))
        .flatMap(face => triangulate(face));

    return { vertices, indices };
}
