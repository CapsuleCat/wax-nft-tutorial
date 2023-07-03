import { collectionName, name } from "./utilities/name.mjs";
import socials from "./utilities/socials.mjs";
import { transact } from "./utilities/transact.mjs";

const template = [
    { "key": "name", "value": ["string", "Baby Chick Egg"] },
    { "key": "img", "value": ["string", "QmTAJmKRFUo4SnmKiq6ixM4FuhAQeReHuCBKE1NZZRpkM9"] },
    { "key": "description", "value": ["string", "Baby Chick Egg for hatching"] },
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

async function createChickEggTemplates() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        return await transact([
            {
                account: "atomicassets",
                name: "createtempl",
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
                    transferable: true,
                    burnable: true,
                    max_supply: 100,
                    immutable_data: template
                },
            },
        ])
    } catch (error) {
        console.error(error);
        return false;
    }
}

(async () => {
    const result = await createChickEggTemplates();
    console.log("Result", result);
})();
