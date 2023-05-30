import { transact } from "./utilities/transact";

const data = [
    { "key": "name", "value": ["string", "Baby Chicks"] },
    { "key": "img", "value": ["string", ""] },
    { "key": "description", "value": ["string", "This is a collection created for tutorials"] },
    { "key": "url", "value": ["string", "https://capsulecat.com"] },
    {
        "key": "socials", "value": ["string", JSON.stringify({
            "twitter": "thecapsulecat",
            "github": "capsulecat",
            // Other examples
            // "facebook": "myfacebook",
            // "medium": "mymedium",
            // "telegram": "mytelegram",
            // "youtube": "myyoutube",
            // "discord": "mydiscord"
        })]
    },
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
            "banner_1920x500": "",
            "logo_512x512": ""
        })]
    }
]

async function createCollection() {
    const author = process.env.WAX_ACCOUNT;

    if (!author) {
        throw new Error("Missing WAX_ACCOUNT");
    }

    try {
        await transact([
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
                    collection_name: name('babychicks'),
                    allow_notify: true,
                    authorized_accounts: [],
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
    console.log(result);
})()