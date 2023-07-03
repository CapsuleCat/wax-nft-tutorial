import { collectionName, name } from "./utilities/name.mjs";
import socials from "./utilities/socials.mjs";
import { transact } from "./utilities/transact.mjs";

const templateEpic = [
    { "key": "name", "value": ["string", "Epic Baby Chick"] },
    { "key": "img", "value": ["string", "QmUwqZ64McMgzzP9Hv1qXvEUaubcHQZwAVpdfjKpn9M5vv"] },
    { "key": "description", "value": ["string", "Epic baby chick"] },
    { "key": "rarity", "value": ["string", "Epic"] },
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

const templateRare = [
    { "key": "name", "value": ["string", "Rare Baby Chick"] },
    { "key": "img", "value": ["string", "QmdQsG8JNfPSSxNzHE5gwhHmBSJNVYaWLWYwpYpEGX8UJ6"] },
    { "key": "description", "value": ["string", "Rare baby chick"] },
    { "key": "rarity", "value": ["string", "Rare"] },
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

const templateCommon = [
    { "key": "name", "value": ["string", "Common Baby Chick"] },
    { "key": "img", "value": ["string", "Qmd2FHnTHw3ernkYegh2xNQK1FFKTd8PwA21ToRhGLvddz"] },
    { "key": "description", "value": ["string", "Common baby chick"] },
    { "key": "rarity", "value": ["string", "Common"] },
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

async function createBabyChickTemplates() {
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
                    schema_name: name('babychick'),

                    transferable: true,
                    burnable: true,
                    max_supply: 10,
                    immutable_data: templateEpic
                },
            },
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
                    schema_name: name('babychick'),

                    transferable: true,
                    burnable: true,
                    max_supply: 20,
                    immutable_data: templateRare
                },
            },
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
                    schema_name: name('babychick'),

                    transferable: true,
                    burnable: true,
                    max_supply: 70,
                    immutable_data: templateCommon
                },
            },
        ])
    } catch (error) {
        console.error(error);
        return false;
    }
}

(async () => {
    const result = await createBabyChickTemplates();
    console.log("Result", result);
})();
