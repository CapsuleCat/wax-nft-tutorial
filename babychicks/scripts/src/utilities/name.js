/**
 * Make sure the name is a valid eosio name
 */
export function name(str) {
    if (str.length > 12) {
        throw new Error("Name too long");
    }

    const charmap = ".12345abcdefghijklmnopqrstuvwxyz";

    for (const c of str) {
        if (charmap.indexOf(c) === -1) {
            throw new Error("Invalid character in name");
        }
    }

    // Last character can't be a dot
    if (str[str.length - 1] === ".") {
        throw new Error("Last character can't be a dot");
    }

    // Last character can't be after the letter 'j'
    if (charmap.indexOf(str[str.length - 1]) > 16) {
        throw new Error("Last character can't be after the letter 'j'");
    }

    return str;
}