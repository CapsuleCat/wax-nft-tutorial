import { transact } from "./utilities/transact.mjs";
import { name } from "./utilities/name.mjs";

async function mintChickEggViaSmartContract() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        return await transact([
            {
                account: author,
                name: "airdropegg",
                authorization: [
                    {
                        actor: author,
                        permission: "active",
                    },
                ],
                data: {
                    receiver: name(author),
                },
            },
        ])
    } catch (error) {
        console.error(error);
        return false;
    }
}

(async () => {
    const result = await mintChickEggViaSmartContract();
    console.log("Result", result);
})();
