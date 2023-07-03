import { createApiRpc } from "./createApiRpc.mjs";

const TAPOS = {
    blocksBehind: 3,
    expireSeconds: 30,
};

export function transact(actions) {
    const apiRpc = createApiRpc();

    return apiRpc.transact({ actions }, TAPOS);
}