import fetch from 'node-fetch';
import { Api, JsonRpc } from "eosjs";
import { JsSignatureProvider } from "eosjs/dist/eosjs-jssig.js";

export function createApiRpc() {
    const privateKey = process.env.WAX_PRIVATE_KEY;
    const endpoint = process.env.WAX_ENDPOINT;

    if (!privateKey) {
        throw new Error("Missing WAX_PRIVATE_KEY");
    }

    if (!endpoint) {
        throw new Error("Missing WAX_ENDPOINT");
    }

    const signatureProvider = new JsSignatureProvider([privateKey]);

    const rpc = new JsonRpc(endpoint, {
        fetch,
    });

    const apiRpc = new Api({
        rpc,
        signatureProvider,
        textDecoder: new TextDecoder(),
        textEncoder: new TextEncoder(),
    });

    return apiRpc;
}