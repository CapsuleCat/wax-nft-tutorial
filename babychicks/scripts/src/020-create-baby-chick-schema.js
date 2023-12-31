import { transact } from "./utilities/transact.mjs";
import { collectionName, name } from "./utilities/name.mjs";

const schema = [
    { "name": "name", "type": "string" },
    { "name": "img", "type": "image" },
    { "name": "description", "type": "string" },
    { "name": "rarity", "type": "string" },
    { "name": "url", "type": "string" },
    { "name": "socials", "type": "string" },
    { "name": "created_at", "type": "uint64" },
    { "name": "hp", "type": "uint64" },
    { "name": "color", "type": "string" },
    { "name": "weight", "type": "uint64" },
]

async function createBabyChickSchema() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        return await transact([
            {
                account: "atomicassets",
                name: "createschema",
                authorization: [
                    {
                        actor: author,
                        permission: "active",
                    },
                ],
                data: {
                    authorized_creator: author,
                    collection_name: collectionName('babychicknft'),
                    schema_name: name('babychick'),
                    schema_format: schema
                },
            },
        ])
    } catch (error) {
        console.error(error);
        return false;
    }
}

(async () => {
    const result = await createBabyChickSchema();
    console.log("Result", result);
})();
