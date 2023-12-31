import { transact } from "./utilities/transact.mjs";
import { collectionName, name } from "./utilities/name.mjs";

const schema = [
    { "name": "name", "type": "string" },
    { "name": "img", "type": "image" },
    { "name": "description", "type": "string" },
    { "name": "url", "type": "string" },
    { "name": "socials", "type": "string" },
    { "name": "created_at", "type": "uint64" }
];

async function createChickEggSchema() {
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
                    schema_name: name('chickegg'),
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
    const result = await createChickEggSchema();
    console.log("Result", result);
})();
