

let setColor;
let takeScreenshot;
let toggleEraser;

Module.onRuntimeInitialized = function() {
    console.log("Module loaded");
    setColor = Module.cwrap('setColor', null, ['number']);
    takeScreenshot = Module.cwrap('makeScreenshot', null, ['string']);
    toggleEraser = Module.cwrap('toggleEraser', null, []);
}


function buttonColorChange(e){
    let color = Number(e.target.value.replace("#", "0x"));
    setColor(color);
}

function takeScreenShot(){
    let name = document.querySelector('#screenshot-name').value
    takeScreenshot(name);
}

function tEraser(){
    toggleEraser();
}


// this is called by c library

function saveFileFromMEMFSToDisk(memoryFSname, localFSname)     // This can be called by C/C++ code
{
    let isSafari = /^((?!chrome|android).)*safari/i.test(navigator.userAgent);
    let data = FS.readFile(memoryFSname);
    let blob;

    if (isSafari) blob = new Blob([data.buffer], { type: "image/png" });
    else blob = new Blob([data.buffer], { type: "image/png" });

    let link = window.URL.createObjectURL(blob);
    download(link, localFSname);
}

function download(url, name) {
    const link = document.createElement('a');
    link.href = url;
    link.download = name;
    link.click();
}
