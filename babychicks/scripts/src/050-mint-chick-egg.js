import { transact } from "./utilities/transact.mjs";
import { collectionName, name } from "./utilities/name.mjs";

const nftData = [
    { "key": "created_at", "value": ["uint64", Date.now()] },
];

async function mintChickEgg() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    const templateId = process.env.TEMPLATE_ID;

    if (!templateId) {
        throw new Error("Missing TEMPLATE_ID");
    }

    try {
        return await transact([
            {
                account: "atomicassets",
                name: "mintasset",
                authorization: [
                    {
                        actor: author,
                        permission: "active",
                    },
                ],
                data: {
                    authorized_minter: author,
                    collection_name: collectionName('babychicknft'),
                    schema_name: name('chickegg'),
                    new_asset_owner: author,
                    template_id: templateId,
                    immutable_data: nftData,
                    mutable_data: [],
                    tokens_to_back: [],
                },
            },
        ])
    } catch (error) {
        console.error(error);
        return false;
    }
}

(async () => {
    const result = await mintChickEgg();
    console.log("Result", result);
})();
