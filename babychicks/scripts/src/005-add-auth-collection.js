import { transact } from "./utilities/transact.mjs";
import { collectionName, name } from "./utilities/name.mjs";

async function createCollection() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        return await transact([
            {
                account: "atomicassets",
                name: "addcolauth",
                authorization: [
                    {
                        actor: author,
                        permission: "active",
                    },
                ],
                data: {
                    collection_name: collectionName('babychicknft'),
                    account_to_add: name(author),
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