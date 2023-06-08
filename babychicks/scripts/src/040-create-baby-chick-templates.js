import { name } from "./utilities/name";
import socials from "./utilities/socials";

const templateEpic = [
    { "key": "name", "value": ["string", "Epic Baby Chick"] },
    // TODO ipfs image string
    { "key": "img", "value": ["image", ""] },
    { "key": "description", "value": ["string", "Epic baby chick"] },
    { "key": "rarity", "value": ["string", "Epic"] },
    // TODO view url
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

const templateRare = [
    { "key": "name", "value": ["string", "Rare Baby Chick"] },
    // TODO ipfs image string
    { "key": "img", "value": ["image", ""] },
    { "key": "description", "value": ["string", "Rare baby chick"] },
    { "key": "rarity", "value": ["string", "Rare"] },
    // TODO view url
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

const templateCommon = [
    { "key": "name", "value": ["string", "Common Baby Chick"] },
    // TODO ipfs image string
    { "key": "img", "value": ["image", ""] },
    { "key": "description", "value": ["string", "Common baby chick"] },
    { "key": "rarity", "value": ["string", "Common"] },
    // TODO view url
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

async function createBabyChickTemplates() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        await transact([
            {
                account: "atomicassets",
                name: "createtempl",
                authorization: [
                    {
                        actor: auth,
                        permission: "active",
                    },
                ],
                data: {
                    authorized_creator: auth,
                    collection_name: name('babychicks'),
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
                        actor: auth,
                        permission: "active",
                    },
                ],
                data: {
                    authorized_creator: auth,
                    collection_name: name('babychicks'),
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
                        actor: auth,
                        permission: "active",
                    },
                ],
                data: {
                    authorized_creator: auth,
                    collection_name: name('babychicks'),
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
    console.log(result);
})();
