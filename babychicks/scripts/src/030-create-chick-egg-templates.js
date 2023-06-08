import { name } from "./utilities/name";
import socials from "./utilities/socials";

const template = [
    { "key": "name", "value": ["string", "Baby Chick Egg"] },
    // TODO ipfs image string
    { "key": "img", "value": ["image", ""] },
    { "key": "description", "value": ["string", "Baby Chick Egg for hatching"] },
    // TODO hatching url
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    { "key": "socials", "value": ["string", JSON.stringify(socials)] }
];

async function createChickEggTemplates() {
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
    console.log(result);
})();
