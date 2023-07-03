import { transact } from "./utilities/transact.mjs";
import { collectionName, name } from "./utilities/name.mjs";
import socials from "./utilities/socials.mjs";

const data = [
    { "key": "name", "value": ["string", "Baby Chicks"] },
    { "key": "img", "value": ["string", "QmRTg2dhvSR7Lbmwvfv4z5c7Eisj7Lb199wsc5ijXHGEBZ"] },
    { "key": "description", "value": ["string", "This is a collection created for tutorials"] },
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] },
    {
        "key": "creator_info", "value": ["string", JSON.stringify({
            "address": "",
            "company": "",
            "name": "",
            "registration_number": ""
        })]
    },
    {
        "key": "images", "value": ["string", JSON.stringify({
            // "banner_1920x500": "",
            "logo_512x512": "QmRTg2dhvSR7Lbmwvfv4z5c7Eisj7Lb199wsc5ijXHGEBZ"
        })]
    }
]

async function createCollection() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        return await transact([
            {
                account: "atomicassets",
                name: "createcol",
                authorization: [
                    {
                        actor: author,
                        permission: "active",
                    },
                ],
                data: {
                    author,
                    collection_name: collectionName('babychicknft'),
                    allow_notify: true,
                    authorized_accounts: [
                        name(author),
                    ],
                    notify_accounts: [],
                    market_fee: 0.05,
                    data: data,
                },
            },
        ])
    } catch (error) {
        console.error(error);
        return false;
    }
}

(async () => {
    const result = await createCollection();
    console.log("Result", result);
})()