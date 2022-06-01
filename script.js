

let setColor;
let takeScreenshot;

Module.onRuntimeInitialized = function() {
    console.log("Module loaded");
    setColor = Module.cwrap('setColor', null, ['string']);
    takeScreenshot = Module.cwrap('makeScreenshot', null, ['string']);
}



function buttonColorChange(col){
    setColor(col);
}

function takeScreenShot(){
    const time = new Date().getTime();
    takeScreenshot("screenshot-"+ time);
}


function saveFileFromMEMFSToDisk(memoryFSname, localFSname)     // This can be called by C/C++ code
{
    let isSafari = /^((?!chrome|android).)*safari/i.test(navigator.userAgent);
    let data = FS.readFile(memoryFSname);
    let blob;

    if (isSafari) blob = new Blob([data.buffer], { type: "image/png" });
    else blob = new Blob([data.buffer], { type: "image/png" });

    let link = window.URL.createObjectURL(blob);
    download(link);
}

function download(url){
    const link = document.createElement('a');
    link.href = url;
    link.download = "screenshot.png";
    link.click();
}
