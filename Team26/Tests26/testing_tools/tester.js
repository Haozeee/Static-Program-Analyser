const fs = require("fs");
const { spawn } = require("child_process");

const rootDir = `${__dirname}/../`;
const autotester = `${rootDir}/autotester.exe`;
const resultFolder = `${rootDir}/results`;

if (!fs.existsSync(resultFolder)) {
    fs.mkdir("../results", (err) => {
        if (err) {
            console.log(err);
        }
    });
}

fs.readdir(rootDir, { withFileTypes: true }, (err, baseFolder) => {
    if (err) {
        console.log(err);
    }
    baseFolder
        .filter(
            (f) => f.isDirectory() && f.name != "Indevelopment" && f.name != "results" && f.name != "testing_tools"
        )
        .map((x) => x.name)
        .forEach((subFolder) => {
            fs.readdir(
                `${rootDir}/${subFolder}`,
                { withFileTypes: true },
                (err, testFiles) => {
                    testFiles
                        .filter(
                            (testFile) =>
                                testFile.name.substring(testFile.name.length - 5) === `e.txt`
                        )
                        .forEach((file) => {
                            const preDir = `${rootDir}/${subFolder}/`;

                            const source = `${preDir}${file.name}`;
                            const query = `${preDir}${file.name.replace(
                                "source",
                                "queries"
                            )}`;
                            const out = `${rootDir}/results/${file.name.replace(
                                "_source.txt",
                                ".xml"
                            )}`;

                            const args = [source, query, out];

                            spawn(autotester, args);
                        });
                }
            );
        });
});
