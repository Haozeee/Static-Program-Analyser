const fs = require("fs");
const path = require("path");
const https = require("https");
const { spawn } = require("child_process");

const rootDir = __dirname;
const autotester = `${rootDir}/autotester`;
const resultFolder = `${rootDir}/results`;
const hostname = process.argv[2];

if (!fs.existsSync("results")) {
    fs.mkdir("results", (err) => {
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
            (f) => f.isDirectory() && f.name != "Indevelopment" && f.name != "results"
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

fs.readdir(resultFolder, (err, results) => {
    const options = {
        hostname: hostname,
        method: `POST`,
        headers: {
            "Content-Type": "text/xml",
        },
    };
    
    results.forEach((result) => {
        const xmlData = fs.readFileSync(`${resultFolder}/${result}`, "utf-8");

        const req = https.request(options, (res) => {
            if (err) {
                console.log(err);
            } else {
                console.log(res);
            }

            res.on("data", (d) => { });
        });

        req.on("error", (err) => {
            console.log(err.message);
        });
        req.write(xmlData);
        req.end();
    });
});
